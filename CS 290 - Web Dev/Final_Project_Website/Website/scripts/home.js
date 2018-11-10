let slideIndex = 0;

function carousel() {
    let i;
    let pictures = document.getElementsByClassName("slide");
    for (i = 0; i < pictures.length; i++) {
       pictures[i].style.display = "none";
    }
    slideIndex++;

    if (slideIndex > pictures.length) {
      slideIndex = 1
    }
    pictures[slideIndex-1].style.display = "block";
    setTimeout(carousel, 5000);
}

document.addEventListener("DOMContentLoaded", function(){
  carousel();
});
