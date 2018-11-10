hoistMe();

function hoistMe(){
  console.log("Hello!");
}

incorrectCall(1, 5);

incorrectCall = function(num1, num2){
  var sum = num1 + num2;
  console.log("The sum of " + num1 + " and " + num2 + " is " + sum);
}
