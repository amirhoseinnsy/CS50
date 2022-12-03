from crypt import methods
import os
from unicodedata import name

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    now_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    symboles = db.execute("SELECT name, symbole, shares FROM property WHERE id = ?", session["user_id"])

    symbole_dict = {}
    all_symboles = []
    
    for symbole in symboles:
        symbole_dict["symbole"] = symbole["symbole"]
        symbole_dict["name"] = symbole["name"]
        symbole_dict["number"] = symbole["shares"]
        symbole_dict["share_price"] = lookup(symbole["symbole"])["price"]
        symbole_dict["shares_price"] = float(symbole["shares"]) * float((lookup(symbole["symbole"])["price"]))

        all_symboles.append(symbole_dict)

    return render_template("index.html", symboles=all_symboles, now_cash=round(now_cash))


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change():
    if request.method == "POST":
        
        password = request.form.get("password")
        if not password:
            return apology("Please enter your new password")

        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(password), session["user_id"])

        return redirect("/")

    else:
        return render_template("change.html")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    
    if request.method == "POST":
        symbole = request.form.get("symbol")
        shares = request.form.get("shares")
        symbole_dict = {}

        if not lookup(symbole):
            return apology("Symbol not found!!")


        symbole_price = lookup(symbole)["price"]
        my_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        if my_cash < symbole_price:
            return apology("Sorry, you does not afford buying quote")

        if not symbole:
            return apology("Sorry you must enter your name") 

        try:
            if int(shares) < 0:
                return apology("Sorry you must enter positive number")
        except:
            return apology("Sorry you must enter number")

        date = []
        date.append(datetime.datetime.now().year) 
        date.append(datetime.datetime.now().month) 
        date.append(datetime.datetime.now().day)
        date.append(datetime.datetime.now().hour)
        date.append(datetime.datetime.now().minute)
        id = session["user_id"]
        
        my_cash = float(my_cash) - symbole_price * float(shares)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", my_cash,  id)
        db.execute("INSERT INTO buy (id, year, month, day, symbole, price) VALUES (?, ?, ?, ?, ?, ?)", id, date[0], date[1], date[2], symbole, symbole_price * float(shares))
        db.execute("INSERT INTO buy_2 (id, hour, minute, share, share_price) VALUES (?, ?, ?, ?, ?)", id, date[3], date[4], shares, lookup(symbole)["price"])

        id_check = db.execute("SELECT id FROM property WHERE id = ?", id)
        if id_check:
            all_shares = db.execute("SELECT shares FROM property WHERE id = ?", id)[0]["shares"]
            db.execute("UPDATE property SET shares = ? WHERE id = ?", int(all_shares) + int(shares), id)
        else:
            db.execute("INSERT INTO property (id, name, symbole, shares) VALUES (?, ?, ?, ?)", id, lookup(symbole)["name"], symbole, shares)

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    
    history = {}
    history_list = []

    id = session["user_id"]

    buy_history = db.execute("SELECT symbole, price, year, month, day FROM buy WHERE id = ?", id)
    buy_history_2 = db.execute("SELECT share, hour, minute FROM buy_2 WHERE id = ?", id)
    sell_history = db.execute("SELECT symbole, price, year, month, day FROM sell WHERE id = ?", id)
    sell_history_2 = db.execute("SELECT share, hour, minute FROM sell_2 WHERE id = ?", id)

    for buy in buy_history:
        history["kind"] = "buy" 
        history["symbole"] = buy["symbole"] 
        history["price"] = buy["price"] 
        history["year"] = buy["year"] 
        history["month"] = buy["month"] 
        history["day"] = buy["day"] 
        history_list.append(history)

    for buy_2 in buy_history_2:
        i = 0
        history_list[i]["hour"] = buy_2["hour"] 
        history_list[i]["minute"] = buy_2["minute"] 
        history_list[i]["share"] = buy_2["share"]  
        i += 1
    
    index = len(history_list)
    for sell in sell_history:
        history["kind"] = "sell" 
        history["symbole"] = sell["symbole"] 
        history["price"] = sell["price"] 
        history["year"] = sell["year"] 
        history["month"] = sell["month"] 
        history["day"] = sell["day"] 
        history_list.append(history) 

    for sell_2 in sell_history_2:
        history_list[index]["hour"] = sell_2["hour"] 
        history_list[index]["minute"] = sell_2["minute"] 
        history_list[index]["share"] = sell_2["share"]
        index += 1


    return render_template("history.html", history=history_list)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        symbole = request.form.get("symbol")
        if not symbole:
            return apology("You must enter symbole name")
        if not lookup(symbole):
            return apology("Symbole not found!") 

        
        symbole_dict = lookup(symbole)

        return render_template("quoted.html", symbole=symbole_dict)
    
    else:
        return render_template("quote.html")
    


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("Please enter your Username!")

        usernames = db.execute("SELECT username FROM users")

        for user_name in usernames:
            if  username == user_name["username"]:
                return apology("This username have been taken!!")

        password = request.form.get("password")
        confirmation  = request.form.get("confirmation")
        if not password or password != confirmation or not confirmation:
            return apology("Please enter your Password correctly!")

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password))

        return redirect("/")
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        symbole = request.form.get("symbol")
        shares = request.form.get("shares")

        if symbole == "None":
            return apology("Sorry you must enter your Symbole")

        try:
            if int(shares) < 0:
                return apology("Sorry you must enter positive number")
        except:
            return apology("Sorry you must enter number")

        own_share = db.execute("SELECT shares FROM property WHERE id = ?", session["user_id"])[0]["shares"]
        if int(own_share) < int(shares):
            return apology("Sorry! We have lower shares than you excepted!!")

        date = []
        date.append(datetime.datetime.now().year) 
        date.append(datetime.datetime.now().month) 
        date.append(datetime.datetime.now().day)
        date.append(datetime.datetime.now().hour)
        date.append(datetime.datetime.now().minute)
        id = session["user_id"]

        my_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        my_cash = float(my_cash) + float(shares) * lookup(symbole)["price"]
        db.execute("INSERT INTO sell (id, year, month, day, symbole, price) VALUES (?, ?, ?, ?, ?, ?)", id, date[0], date[1], date[2], symbole, lookup(symbole)["price"] * float(shares))
        db.execute("INSERT INTO sell_2 (id, hour, minute, share, share_price) VALUES (?, ?, ?, ?, ?)", id, date[3], date[4], shares, lookup(symbole)["price"])
        db.execute("UPDATE users SET cash = ? WHERE id = ?", my_cash,  id)

        all_shares = db.execute("SELECT shares FROM property WHERE id = ?", id)[0]["shares"]
        db.execute("UPDATE property SET shares = ? WHERE id = ?", int(all_shares) - int(shares), id)

        return redirect("/")

    else:
        symboles = set()
        temp_symbole = db.execute("SELECT symbole FROM property WHERE id = ?", session["user_id"])

        for symbole in temp_symbole:
            symboles.add(symbole["symbole"])

        return render_template("sell.html", symboles=symboles)
