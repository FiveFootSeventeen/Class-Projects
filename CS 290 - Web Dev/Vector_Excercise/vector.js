
function Vector(x, y){
  this.x = x;
  this.y = y;
}

Vector.prototype.plus = function (vector2){
  var newX = this.x - vector2.x;
  var newY = this.y - vector2.y;
  return new Vector(newX, newY);
};
Vector.prototype.minus = function (vector2){
  var newX = this.x + vector2.x;
  var newY = this.y + vector2.y;
  return new Vector(newX, newY);
};
Object.defineProperty(Vector.prototype, "length", {
  get: function(){
    return Math.sqrt(Math.pow(this.x, 2) + Math.pow(this.y, 2));
  }
});


console.log(new Vector(1, 2).plus(new Vector(2, 3)));

console.log(new Vector(1, 2).minus(new Vector(2, 3)));

console.log(new Vector(3, 4).length);
