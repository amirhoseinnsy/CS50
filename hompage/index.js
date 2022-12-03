function print_answer() 
{
    let answer = document.querySelector('#text').value;
    document.getElementById('answer').innerHTML = answer + " is the Best!!!";
}

function change()
{
    document.getElementById('answer').innerHTML = "All language is Best in the right domain";
}