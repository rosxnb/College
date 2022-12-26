"use strict";

const btntxt   = document.querySelector("#btn-txt");
const button   = document.querySelector("button");
const input    = document.querySelector("input");
const over_out = document.querySelector("#over-out");
const up_down  = document.getElementById("up-down");
const txtarea  = document.querySelector("#textarea");

button.onclick = function() {
  btntxt.textContent = "Clicked Sucessfully!";
}

document.addEventListener("keydown", (event) => {
  if (event.key === "Enter")
    input.value = "";
});

const handler_mouseover = function() {
  this.style.backgroundColor = "#ed42c0";
  this.style.border = "2px solid black";
}

over_out.addEventListener("mouseover", handler_mouseover);
over_out.addEventListener("mouseout", function() {
  this.style.backgroundColor = "#968391";
  this.style.border = "1px dashed #784e28";
});

const new_element = document.createElement("p");
new_element.classList.add("dynamic-element");
new_element.textContent = "This element is added dynamically";
new_element.style.marginTop = "10px";
new_element.style.color = "white";

const new_element_copy = new_element.cloneNode(true);
new_element_copy.style.marginTop = "0";
new_element_copy.style.marginBottom = "10px";

function handler_mousedown() {
  this.append(new_element);
  this.prepend(new_element_copy);
}

function handler_mouseup() {
  new_element.remove();
  new_element_copy.remove();
}

up_down.addEventListener("mousedown", handler_mousedown);
up_down.addEventListener("mouseup", handler_mouseup);

txtarea.addEventListener("click", function(event) {
  this.focus();
  this.style.backgroundColor = "grey";
  this.style.color = "white";

  event.stopPropagation();
});

document.addEventListener("click", () => {
  txtarea.style.color = "transparent";
  txtarea.blur();
});
