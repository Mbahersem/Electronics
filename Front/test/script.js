let one = document.getElementById("one")
let two = document.getElementById("two")

function handleOne () {
    one.style = 'z-index: 1'
    two.style = 'z-index: 2'
}

function handleTwo () {
    two.style = 'z-index: 1'
    one.style = 'z-index: 2'
}

one.addEventListener('click', handleOne)

two.addEventListener('click', handleTwo)
