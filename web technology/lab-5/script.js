"use strict";

const checkboxes = document.querySelectorAll(".checkboxes");
const submit = document.getElementById("submit");

let check_count = 1;
checkboxes.forEach( checkbox => 
    checkbox.addEventListener("change", function() {
        this.checked ? check_count++ : check_count--; 
    })
);


const password1 = document.getElementById("pw1");
const password2 = document.getElementById("pw2");
const valid_password = () => password1.value === password2.value;

submit.addEventListener("click", (event) => {
    if (check_count === 0 || !valid_password()) {
        event.preventDefault();
        check_count ? alert("passwords didn't match") : alert("select a language");
    }
});
