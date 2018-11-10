//
// function forEach(arr, work){
//   for (var i = 0; i < arr.length; i++){
//     work(arr[i]);
//   }
// }
//
// function sumArray(arr){
//   var theSum = 0;
//   function sumIt(num){
//       theSum += num;
//   }
//
//   forEach(arr, sumIt)
//   return theSum;
// }
//
// console.log(sumArray([1,2,3,4,5,6]));


function sumArr(arr){
  var sum = 0;
  arr.forEach(function(v) {sum += v;});
  return sum;
}

console.log(sumArr([2,2,3]));

function dialog(speaker){
  return function(speach){
    return speaker + " says " + speach;
  }
}


var Donald = { name: "Donald Duck"};
Donald.speak = dialog("Donald Duck");
console.log(Donald.speak("Hello there"));
