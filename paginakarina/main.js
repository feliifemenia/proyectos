abrir.addEventListener("click", () => {
    nav.classList.add("visible");
    document.querySelector(".menu-desplegable").style.display = "flex";
})

abrir.addEventListener("click", () => {
    cerrar.classList.add("visible");
})

cerrar.addEventListener("click", () => {
    nav.classList.remove("visible");
    document.querySelector(".menu-desplegable").style.display = "none";
})