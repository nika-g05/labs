const modal = document.getElementById("mymodal");
const btn = document.getElementById("signupBtn");
const span = document.getElementsByClassName("close")[0];
const form = document.getElementById("singupForm");
const errorMessage = document.getElementById("errorMessage");
const successMessage = document.getElementById("successMessage");
const learnMoreBtn = document.getElementById("learnMoreBtn");
const headerSection = document.querySelector(".header");


btn.onclick = function() {
    modal.style.display = "block";
}

span.onclick = function() {
    modal.style.display = "none";
}

window.onclick = function(event) {
    if (event.target == modal) {
        modal.style.display = "none";
    }
}

form.onsubmit = function(event) {
    event.preventDefault();
    const email = document.getElementById("email").value;
    const password = document.getElementById("password").value;

    if (!email || !password) {
        errorMessage.textContent = "Please fill in all the fields";
        return;
    }

    localStorage.setItem('userEmail', email);

    console.log("Email:", email, "Password:", password);
    successMessage.style.display = "block";
    errorMessage.textContent = "";
    form.reset();
}

window.onload = function() {
    const savedEmail = localStorage.getItem('userEmail');
    if (savedEmail) {
        successMessage.textContent = `Welcome back, ${savedEmail}! You are successfully registered!`;
        successMessage.style.display = "block";
    }
}

learnMoreBtn.onclick = function(event) {
    event.preventDefault();
    headerSection.classList.toggle("darkened");
};
