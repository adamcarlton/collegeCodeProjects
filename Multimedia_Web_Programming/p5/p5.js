/* 
Author: Adam Carlton
Project #5
This JS  will fill allow the user to draw circles/rectangles/triangles by choosing the shape from a dropdown menu and the color desired from a dropdown menu. as well as allow for clicking and dragging for a desired height of a shape
*/

//saves me time with localstorage cus im lazy
const canvasName = "paint"

//hold general info
let ci = {
    canvas: null,
    ctx: null,
    currentColor: null,
    currentShape: null,
    mouseDown: false,
    startX: 0,
    startY: 0,
    endX: 0,
    endY: 0
}

//used to create a circle object with a draw method to handle the logic in one place
class Circle{
    constructor(x, y, rad){
        this.x = x
        this.y = y
        this.rad = rad
    }
    draw(){
        ci.ctx.fillStyle = ci.currentColor
        ci.ctx.beginPath()
        ci.ctx.arc(this.x, this.y, this.rad, 0, Math.PI * 2, true)
        ci.ctx.closePath()
        ci.ctx.lineWidth = 5
        ci.ctx.stroke()
        ci.ctx.fill()
    }
}

//used to create a triangle object with a draw method to handle the logic in one place
class Triangle{
    constructor(x, y, h, w){
        this.x = x
        this.y = y
        this.h = h
        this.w = w
    }
    draw(){
        ci.ctx.fillStyle = ci.currentColor
        ci.ctx.beginPath()
        ci.ctx.moveTo(this.x, this.y)
        ci.ctx.lineTo(this.x + .5*this.w, this.y-this.h)
        ci.ctx.lineTo(this.x + this.w, this.y)
        ci.ctx.closePath()
        ci.ctx.lineWidth = 5
        ci.ctx.stroke()
        ci.ctx.fill()
    }
}

//used to create a rectangle/square object with a draw method to handle the logic in one place
class Rect{
    constructor(x, y, h, w){
        this.x = x
        this.y = y
        this.h = h
        this.w = w   
    }
    draw(){
        ci.ctx.fillStyle = ci.currentColor
        ci.ctx.lineWidth = 5
        ci.ctx.beginPath()
        ci.ctx.moveTo(this.x, this.y)
        ci.ctx.lineTo(this.x + this.w, this.y)
        ci.ctx.lineTo(this.x + this.w, this.y - this.h)
        ci.ctx.lineTo(this.x, this.y - this.h)
        ci.ctx.closePath()
        ci.ctx.stroke()
        ci.ctx.fill()
    }
}

//handle loading the page, checking localstorage, setting eventhandlers for the button/dropdown menus/canvas
window.onload = function(){
    ci.canvas = document.querySelector("#"+canvasName)
    ci.ctx = ci.canvas.getContext("2d")
    let shapeDropdown = document.querySelector("#shapeDrop")
    let colorDropdown = document.querySelector("#colorDrop")
    let storedData = localStorage.getItem(canvasName)
    if(storedData!=null){
        let img = new Image()
        img.src = storedData
        img.onload = function(){
            ci.ctx.drawImage(img, 0, 0)
        }
    }
    ci.currentShape = shapeDropdown.options[shapeDropdown.selectedIndex].value
    ci.currentColor = colorDropdown.options[colorDropdown.selectedIndex].value
    shapeDropdown.addEventListener('change', function(){
        ci.currentShape = shapeDropdown.options[shapeDropdown.selectedIndex].value
    })
    colorDropdown.addEventListener('change', function(){
        ci.currentColor = colorDropdown.options[colorDropdown.selectedIndex].value
    })

    document.querySelector("#clear").addEventListener('click', function(){
        ci.ctx.clearRect(0, 0, ci.canvas.width, ci.canvas.height)
        localStorage.removeItem(canvasName)
    })
    ci.canvas.addEventListener('mousedown', function(event){
        ci.mouseDown = true
        ci.startX = event.offsetX
        ci.startY = event.offsetY
    })
    ci.canvas.addEventListener('mousemove', function (event) {
        if(ci.mouseDown){
            ci.endX = event.offsetX
            ci.endY = event.offsetY  
        }
    })
    ci.canvas.addEventListener('mouseup', function (event) {
        ci.mouseDown = false
        switch (ci.currentShape) {
            case "Triangle":
                let t = (ci.startX != event.offsetX || ci.startY != event.offsetY) ? new Triangle(ci.startX, ci.startY, ci.startY - ci.endY, ci.endX - ci.startX) : new Triangle(event.offsetX, event.offsetY, 100, 100)
                t.draw()
                localStorage.setItem(canvasName, ci.canvas.toDataURL())
                break
            case "Circle":
                let c = (ci.startX != event.offsetX || ci.startY != event.offsetY) ? new Circle(ci.startX, ci.startY, Math.max(Math.abs(ci.startY - ci.endY), Math.abs(ci.endX - ci.startX))) : new Circle(event.offsetX, event.offsetY, 50)
                c.draw()
                localStorage.setItem(canvasName, ci.canvas.toDataURL())
                break
            case "Rectangle":
                let r = (ci.startX != event.offsetX || ci.startY != event.offsetY) ? new Rect(ci.startX, ci.startY, ci.startY - ci.endY, ci.endX - ci.startX) : new Rect(event.offsetX, event.offsetY, 50, 100)
                r.draw()
                localStorage.setItem(canvasName, ci.canvas.toDataURL())
                break
        }
    })
}