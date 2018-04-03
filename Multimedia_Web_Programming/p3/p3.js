/* 
Author: Adam Carlton
Project #3
This JS  will fill a dropdown menu with possible background colors, handle events to change the background color, draw text, and to clear the canvas to the current background color as well as draw a few things.
*/


//holds the x and y coords for the truck I draw
class truckLocation{
    constructor(x, y){
        this.x=x
        this.y=y
    }
}


//object to hold the relevant info needed.
let canvasInfo = {
    canvas: null,
    context: null,
    truckX: null,
    truckY: null,
    image: null,
    imageX: null,
    imageY: null
}


//global variable so i can deal with entering more than one message on the same color background. 
let currentText=""


//populates the dropdown menu with color options
function populateDropdown(){
    let dropdownMenu = document.querySelector('#dropdown')
    
    let aqua = document.createElement('option')
    aqua.text = "Aqua"
    
    let aquamarine = document.createElement('option')
    aquamarine.text = "Aquamarine"

    let lightPink = document.createElement('option')
    lightPink.text = "LightPink"

    let orchid = document.createElement('option')
    orchid.text = "Orchid"

    let purple = document.createElement('option')
    purple.text = "Purple"

    dropdownMenu.appendChild(aqua)
    dropdownMenu.appendChild(aquamarine)
    dropdownMenu.appendChild(lightPink)
    dropdownMenu.appendChild(orchid)
    dropdownMenu.appendChild(purple)
}

//draws a sun in the corner
function drawSun(){
    canvasInfo.context.fillStyle = "yellow"
    canvasInfo.context.beginPath()
    canvasInfo.context.arc(25, 25, 100, 0, 2*Math.PI)
    canvasInfo.context.closePath()
    canvasInfo.context.stroke()
    canvasInfo.context.lineWidth = 1
    canvasInfo.context.strokeStyle = "black"
    canvasInfo.context.fill()
}


//draws the truck for the canvas. as well as draws the wheels. 
function drawTruck(){
    //make the outline of the truck
    canvasInfo.context.beginPath()
    canvasInfo.context.moveTo(canvasInfo.truckX, canvasInfo.truckY)
    canvasInfo.context.lineTo(canvasInfo.truckX + 400, canvasInfo.truckY)
    canvasInfo.context.moveTo(canvasInfo.truckX + 400, canvasInfo.truckY)
    canvasInfo.context.lineTo(canvasInfo.truckX + 400, canvasInfo.truckY-75)
    canvasInfo.context.moveTo(canvasInfo.truckX + 400, canvasInfo.truckY - 75)
    canvasInfo.context.lineTo(canvasInfo.truckX + 330, canvasInfo.truckY - 75)
    canvasInfo.context.moveTo(canvasInfo.truckX + 330, canvasInfo.truckY - 75)
    canvasInfo.context.lineTo(canvasInfo.truckX + 250, canvasInfo.truckY - 150)
    canvasInfo.context.moveTo(canvasInfo.truckX + 250, canvasInfo.truckY - 150)
    canvasInfo.context.lineTo(canvasInfo.truckX + 150, canvasInfo.truckY - 150)
    canvasInfo.context.moveTo(canvasInfo.truckX + 150, canvasInfo.truckY - 150)
    canvasInfo.context.lineTo(canvasInfo.truckX + 150, canvasInfo.truckY - 75)
    canvasInfo.context.moveTo(canvasInfo.truckX + 150, canvasInfo.truckY - 75)
    canvasInfo.context.lineTo(canvasInfo.truckX, canvasInfo.truckY - 75)
    canvasInfo.context.moveTo(canvasInfo.truckX, canvasInfo.truckY - 75)
    canvasInfo.context.lineTo(canvasInfo.truckX, canvasInfo.truckY)
    canvasInfo.context.closePath()
    canvasInfo.context.lineWidth = 1
    canvasInfo.context.strokeStyle = "black"
    canvasInfo.context.stroke()

    //make the first wheel
    canvasInfo.context.fillStyle = "SlateGray"
    canvasInfo.context.beginPath()
    canvasInfo.context.arc(canvasInfo.truckX + 75, canvasInfo.truckY+7, 40, 0, 2*Math.PI)
    canvasInfo.context.closePath()
    canvasInfo.context.stroke()
    canvasInfo.context.lineWidth = 1
    canvasInfo.context.strokeStyle = "black"
    canvasInfo.context.fill()

    //make the second wheel
    canvasInfo.context.fillStyle = "SlateGray"
    canvasInfo.context.beginPath()
    canvasInfo.context.arc(canvasInfo.truckX + 325, canvasInfo.truckY + 7, 40, 0, 2 * Math.PI)
    canvasInfo.context.closePath()
    canvasInfo.context.stroke()
    canvasInfo.context.lineWidth = 1
    canvasInfo.context.strokeStyle = "black"
    canvasInfo.context.fill()
}


//creates 40 flowers using a for loop, each with a color from the colorArray
function drawFlowers(){
    let colorArray = ["White", "Crimson", "Chartreuse", "DarkGreen", "Maroon", "DarkOrange", "MediumBlue", "Yellow", "Red", "Olive"]
    for(i = 1; i<=39; i++){
        canvasInfo.context.beginPath()
        canvasInfo.context.moveTo(i*20, 500)
        canvasInfo.context.lineTo(i*20, 480)
        canvasInfo.context.closePath()
        canvasInfo.context.stroke()
        canvasInfo.context.fillStyle = colorArray[i%10]
        canvasInfo.context.beginPath()
        canvasInfo.context.arc(i*20, 475, 10, 0, 2 * Math.PI)
        canvasInfo.context.closePath()
        canvasInfo.context.stroke()
        canvasInfo.context.lineWidth = 1
        canvasInfo.context.strokeStyle = "black"
        canvasInfo.context.fill()
    }
    
}


//draw the astros logo image I have
function drawImage(){
    canvasInfo.context.beginPath()
    canvasInfo.context.drawImage(canvasInfo.image, canvasInfo.imageX, canvasInfo.imageY, canvasInfo.image.width, canvasInfo.image.height)
    canvasInfo.context.closePath()
    canvasInfo.context.beginPath()
    canvasInfo.context.moveTo(148, 98)
    canvasInfo.context.lineTo(352, 98)
    canvasInfo.context.moveTo(352, 98)
    canvasInfo.context.lineTo(352, 300)
    canvasInfo.context.moveTo(352, 300)
    canvasInfo.context.lineTo(148, 300)
    canvasInfo.context.moveTo(148, 300)
    canvasInfo.context.lineTo(148, 98)
    canvasInfo.context.closePath()
    canvasInfo.context.lineWidth = 5
    canvasInfo.context.strokeStyle = "Navy"
    canvasInfo.context.stroke()
}


//clears the canvas and redraws the objects that I have created
function redraw(){
    canvasInfo.context.clearRect(0, 0, canvasInfo.canvas.width, canvasInfo.canvas.height)
    drawImage()
    drawTruck()
    drawFlowers()
    drawSun()
}

//initial setup, instantiate a trucklocation class and store the x and y value in the canvasInfo, set up event handlers for the buttons.
window.onload = function(){
    populateDropdown()
    let t = new truckLocation(250, 450)
    let dropdownMenu = document.querySelector("#dropdown")
    canvasInfo.canvas = document.querySelector("#drawMe")
    canvasInfo.context = canvasInfo.canvas.getContext("2d")
    canvasInfo.truckX = t.x
    canvasInfo.truckY = t.y
    canvasInfo.image = new Image()
    canvasInfo.image.onload = function(){
        let aspectRatio = canvasInfo.image.width/canvasInfo.image.height
        let invAspectRatio = 1.0/aspectRatio
        let width = 200
        canvasInfo.imageX = 150
        canvasInfo.imageY = 100
        canvasInfo.image.width = width
        canvasInfo.image.height = invAspectRatio*width
        drawImage()
    }
    canvasInfo.image.src = "astros.png"
    drawSun()
    drawTruck()
    drawFlowers()
    canvasInfo.canvas.style.backgroundColor = dropdownMenu.options[0].text
    dropdownMenu.addEventListener("change", function(){
        canvasInfo.canvas.style.backgroundColor = dropdownMenu.options[dropdownMenu.selectedIndex].text
        redraw()
    })
    document.querySelector("#drawTxt").addEventListener("click", function(){
        let inputText = document.querySelector("#inputTxt").value
        if(inputText != ""){
            if(currentText!=""){
                redraw()
            }
            currentText = inputText
            canvasInfo.context.font = "50px Arial"
            canvasInfo.context.fillStyle = "Orange"
            canvasInfo.context.fillText(inputText, 200, 50)
            document.querySelector("#inputTxt").value = ""
        }
        else{
            alert("Whoa there cowboy! You needa input some text first.")
        }
    })

    document.querySelector("#clear").addEventListener("click", function(){
        canvasInfo.context.clearRect(0, 0, canvasInfo.canvas.width, canvasInfo.canvas.height)
    })
}