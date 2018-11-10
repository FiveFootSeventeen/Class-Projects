function asTabs(node) {
  var newDiv = document.createElement("div");
  for (var i = 0; i < node.children.length; i++){
    var childName = node.children[i].getAttribute("data-tabname");
    if (i != 0 )
      node.children[i].style.display = "none";
    node.children[i].setAttribute("button-number", (i+1));
    var newButton = document.createElement("button");
    newButton.addEventListener("click", changeTab);
    newButton.setAttribute("button-number", (i+1))
    newButton.textContent = childName;
    newDiv.appendChild(newButton);
  }
  node.insertBefore(newDiv, node.firstChild);
}
asTabs(document.querySelector("#wrapper"));

function changeTab(event){
    var tabs = document.querySelectorAll('[data-tabname]');
    var tabName = event.target.getAttribute("button-number");
    for (var i = 0; i < tabs.length; i++){
      if (tabs[i].getAttribute("button-number") != tabName){
        tabs[i].style.display = "none";
      }
      if(tabs[i].getAttribute("button-number") == tabName)
        tabs[i].style.display = "block";
    }
}
