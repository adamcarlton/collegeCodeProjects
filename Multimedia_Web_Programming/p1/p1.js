/*
Author: Adam Carlton
Project #1
This is javascript will consistently update the time on the html page every 500 milliseconds as well as update the page with quotes and their authors every 5 seconds
*/

function updateCurrentTime(){
    //creates a new Date object and sets the corresponding span
    var currentTime = new Date()
    document.querySelector("#currentTime").innerHTML=currentTime
}
function generateRandomNumber(){
    //generates a random number between 0 and 4
    return Math.floor(Math.random()*5)
}
function setQuote(){
    //sets the quote and author span after retrieving an index in the range 0-4
    var quoteArray = ["Good, better, best. Never let it rest. 'Til your good is better and your better is best", "It does not matter how slowly you go as long as you do not stop.", "It always seems impossible until it's done.", "The secret of getting ahead is getting started.", "If you can dream it, you can do it."]
    var authorArray = ["St. Jerome", "Confucius", "Nelson Mandela", "Mark Twain", "Walt Disney"]
    var index = generateRandomNumber()
    document.querySelector("#quote").innerHTML = quoteArray[index]
    document.querySelector("#author").innerHTML = "-" + authorArray[index]
}
function init(){
    /*
    sets the initial quote and time so upon loading the page there's no delay.
    sets intervals for updating the time every 500 milliseconds and updates the quote/author every 5 seconds.
    */
    setQuote()
    updateCurrentTime()
    setInterval(updateCurrentTime, 500)
    setInterval(setQuote, 5000)
}
window.onload=init