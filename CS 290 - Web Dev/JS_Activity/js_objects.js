

function deepEqual(object1, object2){
  if (object1 == null && object2 == null)
    return true;
  if (typeof(object1) == typeof(object2) && object1 != null && object2 != null){
    for (key in object1){
      if ("undefined" === typeof(object2[key]))
        return false;
      else {
        if (typeof(object1[key]) == "object" && typeof(object2[key]) == "object")
          deepEqual(object1[key], object2[key]);
        else {
          if (object1[key] === object2[key])
            return true;
        }
      }
    }
  }
  return false;
}
