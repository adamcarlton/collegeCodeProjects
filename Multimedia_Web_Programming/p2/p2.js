/*
Author: Adam Carlton
Project #2
This javascript displays a google map in the HTML file, determines current location, places a marker, can center the map based on where the current marker is, can switch locations based on dropdown menu change. Can go right back to current location based on current location button or based on the dropdown menu
*/

const map = {
    map:"",
    latLong:"",
    marker: "",
    location: ""
}
const locations = []

let center = ""

//creates a new Date object and sets the corresponding span
function updateCurrentTime() {
    var currentTime = new Date()
    document.querySelector("#currentTime").innerHTML = currentTime
}

//checks to see if browser has geolocation and if so, jumps to createMap else alerts the user
function currentLocation(){
    if (navigator.geolocation){
        navigator.geolocation.getCurrentPosition(createMap)
    }
    else{
        alert("This browser does not support Geolocation!")
    }
}

//creates the initial map with a marker and info window at the current location determined by the browser
function createMap(position){
    let mapOptions = {
        center: new google.maps.LatLng(position.coords.latitude, position.coords.longitude),
        zoom: 15,
        mapTypeId: google.maps.MapTypeId.HYBRID
    }
    
    const googleMap = new google.maps.Map(document.querySelector("#googleMap"), mapOptions)
    let marker = new google.maps.Marker({
        position: new google.maps.LatLng(position.coords.latitude, position.coords.longitude),
        map: googleMap,
        animation: google.maps.Animation.DROP,
        title:"Current Location"
    })
    map.latLong = new google.maps.LatLng(position.coords.latitude, position.coords.longitude)
    map.map = googleMap
    map.marker = marker
    center = map.latLong
    let geocoder = new google.maps.Geocoder
    geocoder.geocode({'location' : map.latLong}, function(results, status){
        if (status == "OK"){
            map.location = results[0].formatted_address
            updateInfo(map.location, position.coords.latitude, position.coords.longitude)
            let location0 = {description: map.location, latitude: position.coords.latitude, longitude: position.coords.longitude, marker: marker}
            locations[0]=location0
            let infoWindow = new google.maps.InfoWindow({
                content: map.location
            })
            marker.addListener("click", function () {
                infoWindow.open(map, marker)
            })
            populateDropdownList()
        }
        else{
            alert("Geocoding failed due to the following reason: " + status)
        }
    })
    
}

//creates location objects and puts them in the locations array
function populateLocationsArray(){
    let location1 = {description: "Austin, Texas. AKA Live music capital of the world. Austin is the state capital of Texas and is well known for the events held there such as ACL and SXSW.", latitude: 30.2672, longitude: -97.7431, marker: ""}
    let location2 = {description: "Tokyo, Japan. Japan’s busy capital, mixes the ultramodern and the traditional, from neon-lit skyscrapers to historic temples. The opulent Meiji Shinto Shrine is known for its towering gate and surrounding woods. The Imperial Palace sits amid large public gardens. The city's many museums offer exhibits ranging from classical art (in the Tokyo National Museum) to a reconstructed kabuki theater (in the Edo-Tokyo Museum).", latitude: 35.6895, longitude: 139.6917, marker: ""}
    let location3 = { description: "San Francisco, California. It's known for its year-round fog, iconic Golden Gate Bridge, cable cars and colorful Victorian houses. The Financial District's Transamerica Pyramid is its most distinctive skyscraper. In the bay sits Alcatraz Island, site of the notorious former prison.", latitude: 37.7749, longitude: -122.4194, marker: ""}
    let location4 = { description: "Honolulu, Hawaii. Honolulu, on the island of Oahu’s south shore, is capital of Hawaii and gateway to the U.S. island chain. The Waikiki neighborhood is its center for dining, nightlife and shopping, famed for its iconic crescent beach backed by palms and high-rise hotels, with volcanic Diamond Head crater looming in the distance. Sites relating to the World War II attack on Pearl Harbor include the USS Arizona Memorial.", latitude: 21.3069, longitude: -157.8583, marker: ""}
    locations[1]=location1
    locations[2]=location2
    locations[3]=location3
    locations[4]=location4
}

//populates the drop down list with the current location and pre-determined locations
function populateDropdownList(){
    let dropDown = document.querySelector("#dropdown")
    let currentLocOption = document.createElement("option")
    currentLocOption.text = map.location
    let ausTx = document.createElement("option")
    ausTx.text="Austin, Texas"
    let tokyoJap = document.createElement("option")
    tokyoJap.text= "Tokyo, Japan"
    let sanFranCali = document.createElement("option")
    sanFranCali.text="San Francisco, California"
    let honoluluHawaii = document.createElement("option")
    honoluluHawaii.text="Honolulu, Hawaii"
    dropDown.appendChild(currentLocOption)
    dropDown.appendChild(ausTx)
    dropDown.appendChild(tokyoJap)
    dropDown.appendChild(sanFranCali)
    dropDown.appendChild(honoluluHawaii)
    
}

//updates the information span 
function updateInfo(location, latitude, longitude){
    document.querySelector("#location").innerHTML = location
    document.querySelector("#latitude").innerHTML = latitude
    document.querySelector("#longitude").innerHTML = longitude
}

window.onload=function(){
    updateCurrentTime()
    setInterval(updateCurrentTime, 500)
    currentLocation()
    populateLocationsArray()
    let dropDownMenu = document.querySelector("select")
    dropDownMenu.addEventListener("change", function(){
        let selectedLocation = locations[dropDownMenu.selectedIndex]
        let selectedLatLng = new google.maps.LatLng(selectedLocation.latitude, selectedLocation.longitude)
        updateInfo(dropDownMenu.value, selectedLocation.latitude, selectedLocation.longitude)
        map.map.panTo(selectedLatLng)
        if (selectedLocation.marker != ""){
            selectedLocation.marker.setMap(null)
        }
        let marker = new google.maps.Marker({
            position: new google.maps.LatLng(selectedLocation.latitude, selectedLocation.longitude),
            map: map.map,
            animation: google.maps.Animation.DROP,
            title: dropDownMenu.value
        })
        let infoWindow = new google.maps.InfoWindow({
            content: selectedLocation.description
        })
        marker.addListener("click", function () {
            infoWindow.open(map, marker)
        })
        center = new google.maps.LatLng(selectedLocation.latitude, selectedLocation.longitude)
        selectedLocation.marker = marker
    })
    document.querySelector("#currentLoc").addEventListener("click", function(){
        map.map.panTo(map.latLong)
        center = map.latLong
        updateInfo(map.location, map.latLong.lat(), map.latLong.lng())
        document.querySelector("#dropdown").value = document.querySelector("#dropdown").options[0].value
    })
    document.querySelector("#centerBtn").addEventListener("click", function(){
        map.map.panTo(center)
    })
}