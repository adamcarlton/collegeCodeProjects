/* 
Author: Adam Carlton
Project #4
This JS will allow for a user to move around a sprite in the canvas as well as display a video when the sprite reaches a certain location in the canvas
*/

//my sprite sheet and video source
const mySprite = "ogre.png"
let videoPlaying = false
let infiniteFun = false

//canvasInfo
let ci = {
    canvas: null,
    ctx: null,
    numOfFrames: 4,
    img: null,
    imgWidth: 0,
    imgHeight: 0,
    frameIndex: 0,
    frameWidth: 0,
    x: 600,
    y: 290,
    vid: null,
    vidX: null,
    vidY: null,
    vidW: null,
    vidH: null
}

//draw initial background elements
function setBackground(){
    ci.canvas.style.backgroundColor = "Cyan"
    ci.ctx.beginPath()
    ci.ctx.moveTo(0, 350)
    ci.ctx.lineTo(1250, 350)
    ci.ctx.closePath()
    ci.ctx.stroke()

    ci.ctx.beginPath()
    ci.ctx.moveTo(0, 50)
    ci.ctx.lineTo(30, 50)
    ci.ctx.closePath()
    ci.ctx.strokeStyle = "Red"
    ci.ctx.lineWidth = 5
    ci.ctx.stroke()

    ci.ctx.beginPath()
    ci.ctx.moveTo(1220, 50)
    ci.ctx.lineTo(1250, 50)
    ci.ctx.closePath()
    ci.ctx.strokeStyle = "Red"
    ci.ctx.lineWidth = 5
    ci.ctx.stroke()
}

//handles the arrow keys being pressed down
function handleKeyDown(event){
    if(videoPlaying){
        videoPlaying = false
        stopAndHideVideo()
    }
    switch(event.keyCode){
        case 37:
            //left
            moveLeft()
            break
        case 38:
            //up
            moveUp()
            break
        case 39:
            //right
            moveRight()
            break
        case 40:
            //down
            moveDown()
            break
    }

}


//goes back to standing still facing the user
function handleKeyUp(event){
    standStill()
}


//you'll see
function rekt(){
    ci.ctx.font = "50px Arial"
    ci.ctx.fillStyle = "Red"
    ci.ctx.fillText("AIN'T NO BRAKES ON THE RICK ROLL TRAIN", 100, 100)
}


//moves left at a rate of 5 x values at a time. Also detects if the user is in the correct spot for a video to begin playing
function moveLeft(){
    frameHeight = ci.imgHeight
    ci.ctx.clearRect(ci.x, ci.y, ci.frameWidth, frameHeight)
    ci.ctx.drawImage(ci.img, (ci.frameIndex+12) * ci.frameWidth, 0, ci.frameWidth, frameHeight, ci.x, ci.y, ci.frameWidth, frameHeight)
    ci.frameIndex++
    ci.x-=5
    if(ci.frameIndex >= ci.numOfFrames){
        ci.frameIndex = 0
    }
    if(ci.x <= 1){
        ci.x = 2
    }
    if (ci.x <= 2){
        ci.vid.play()
        if (!infiniteFun) {
            videoPlaying = true
        }
        else {
            rekt()
        }
    }
}

//moves right at a rate of 5 x values at a time. Also detects if the user is in the correct spot for a video to begin playing
function moveRight(){
    frameHeight = ci.imgHeight
    ci.ctx.clearRect(ci.x, ci.y, ci.frameWidth, frameHeight)
    ci.ctx.drawImage(ci.img, (ci.frameIndex + 4) * ci.frameWidth, 0, ci.frameWidth, frameHeight, ci.x, ci.y, ci.frameWidth, frameHeight)
    ci.frameIndex++
    ci.x += 5
    if (ci.frameIndex >= ci.numOfFrames) {
        ci.frameIndex = 0
    }
    if(ci.x >= 1200){
        ci.x=1199
    }
    if(ci.x >= 1199){
        ci.vid.play()
        if(!infiniteFun){
            videoPlaying = true
        }
        else{
            rekt()
        }
    }
}

//moves upward at a rate of 1 y value. Higher values would leave trails from the sprite
function moveUp(){
    frameHeight = ci.imgHeight
    ci.ctx.clearRect(ci.x, ci.y, ci.frameWidth, frameHeight)
    ci.ctx.drawImage(ci.img, (ci.frameIndex + 8) * ci.frameWidth, 0, ci.frameWidth, frameHeight, ci.x, ci.y, ci.frameWidth, frameHeight)
    ci.frameIndex++
    ci.y -= 1
    if (ci.frameIndex >= ci.numOfFrames) {
        ci.frameIndex = 0
    }
    if (ci.y <= 10){
        ci.y = 11
    }
}

//moves downward at a rate of 1 y value. Problem here was higher values would leave trails from the sprite.
function moveDown(){
    frameHeight = ci.imgHeight
    ci.ctx.clearRect(ci.x, ci.y, ci.frameWidth, frameHeight)
    ci.ctx.drawImage(ci.img, ci.frameIndex * ci.frameWidth, 0, ci.frameWidth, frameHeight, ci.x, ci.y, ci.frameWidth, frameHeight)
    ci.frameIndex++
    ci.y += 1
    if (ci.frameIndex >= ci.numOfFrames) {
        ci.frameIndex = 0
    }
    if(ci.y >= 291){
        ci.y = 290
    }
}

//makes the sprite stand still on the first animation of the sprite
function standStill(){
        let frameWidth = ci.frameWidth
        let frameHeight = ci.imgHeight
        ci.ctx.clearRect(ci.x, ci.y, frameWidth, frameHeight)
        ci.ctx.drawImage(ci.img, 0, 0, frameWidth, frameHeight, ci.x, ci.y, frameWidth, frameHeight)
}


//will play the video inside the canvas
function playVideo(){
    (function loop(){
        if (!ci.vid.paused && !ci.vid.end){
            ci.ctx.drawImage(ci.vid, ci.vidX, ci.vidY, ci.vidW, ci.vidH)
            setTimeout(loop, 1000/60)
        }
    })()
}

//will pause and hide the video
function stopAndHideVideo(){
    ci.vid.pause()
    ci.ctx.clearRect(ci.vidX, ci.vidY, ci.vidW, ci.vidH)
}

//function to load up canvas information as well as set up event handlers
window.onload = function(){
    ci.canvas = document.querySelector("#draw")
    ci.ctx = ci.canvas.getContext("2d")
    setBackground()
    ci.img = new Image()
    ci.img.onload = function(){
        ci.imgWidth = this.width/4
        ci.imgHeight = this.height/4.5
        ci.frameWidth = ci.imgWidth/ci.numOfFrames
        standStill()
    }
    ci.img.src = mySprite
    ci.vid = document.querySelector('#video')
    ci.vidX = 0
    ci.vidY = 351
    ci.vidH = 199
    ci.vidW = 1250
    document.addEventListener("keydown", handleKeyDown)
    document.addEventListener("keyup", handleKeyUp)
    document.querySelector("#fun").addEventListener("click", function(){
        infiniteFun = true
    })
    ci.vid.addEventListener("play", playVideo)
}