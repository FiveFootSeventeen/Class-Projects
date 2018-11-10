function Automobile( year, make, model, type ){
    this.year = year; //integer (ex. 2001, 1995)
    this.make = make; //string (ex. Honda, Ford)
    this.model = model; //string (ex. Accord, Focus)
    this.type = type; //string (ex. Pickup, SUV)
}

var automobiles = [
    new Automobile(1995, "Honda", "Accord", "Sedan"),
    new Automobile(1990, "Ford", "F-150", "Pickup"),
    new Automobile(2000, "GMC", "Tahoe", "SUV"),
    new Automobile(2010, "Toyota", "Tacoma", "Pickup"),
    new Automobile(2005, "Lotus", "Elise", "Roadster"),
    new Automobile(2008, "Subaru", "Outback", "Wagon")
    ];

Automobile.prototype.logMe = function(printWhat){
  if (printWhat){
    console.log(this.year + " " + this.make + " " + this.model + " " + this.type + "\n");
  }
  else {
    console.log(this.year + " " + this.make + " " + this.model + "\n");
  }
}

/*********************************************************************
** Function: sortArr
** Description: Sort an array according to a given comparator
** Parameters: a comparator function to evaluate two elements of the array
** an array of elements
** Pre-Conditions:
** Post-Conditions: the array is sorted according to the comparator
*********************************************************************/
function sortArr( comparator, array ){
    quickSort(comparator, array, 0, array.length - 1);
    return array;
}

/*********************************************************************
** Function: Swap
** Description: Swap two elements of an array
** Parameters: an array of elements, the locations of the elements to be swapped
** Pre-Conditions:
** Post-Conditions: the values of the elements in the array are swapped
*********************************************************************/
function swap(array, one, two){
  var temp = array[one];
  array[one] = array[two];
  array[two] = temp;
}

//This quicksort code was adapted from an example on youtube channel mycodeschool
//https://www.youtube.com/watch?v=COk73cpQbFQ
/*********************************************************************
** Function: partition
** Description: creates a partition with all elements to the left of the pIndex
** sorted according to the given comparator function
** Parameters: a comparator function, an array of elements, the start position
** of the array, the end position.
** Pre-Conditions:
** Post-Conditions: all elements to the left the index are either greater
** or less than the pivot
*********************************************************************/
function partition(comparator, array, start, end){
  var pivot = end;
  var pIndex = start;
  for (var i = start; i < end; i++){
    if (comparator(array[i], array[pivot])){
      swap(array, i, pIndex);
      pIndex++;
    }
  }
  swap(array, pIndex, pivot)
  return pIndex;
}

//This quicksort code was adapted from an example on youtube channel mycodeschool
//https://www.youtube.com/watch?v=COk73cpQbFQ
/*********************************************************************
** Function: quickSort
** Description: Call to sort an array according to a comparator
** Parameters: a comparator function, an array, the start position, the end
** position
** Pre-Conditions:
** Post-Conditions: the array portion between the start and the end position
** is sorted according to the comparator rule.
*********************************************************************/
function quickSort(comparator, array, start, end){
  if (start < end){
    var pIndex = partition(comparator, array, start, end);
    quickSort(comparator, array, start, pIndex-1);
    quickSort(comparator, array, pIndex+1, end);
  }
}

/*********************************************************************
** Function: yearComparator
** Description: Compares the years of two Automobile objects
** Parameters: two Automobile objects
** Pre-Conditions:
** Post-Conditions: a boolean value is returned
*********************************************************************/
function yearComparator(auto1, auto2){
    if (auto1.year >= auto2.year){
      return true;
    }
    else {
      return false;
    }
}

/*********************************************************************
** Function: makeComparator
** Description: Compares the makes of two Automobile objects
** Parameters: two Automobile objects
** Pre-Conditions:
** Post-Conditions: a boolean value is returned
*********************************************************************/
function makeComparator( auto1, auto2){
    auto1Make = auto1.make.toLowerCase();
    auto2Make = auto2.make.toLowerCase();
    if (auto1Make[0] <= auto2Make[0])
      return true;
    else
      return false;
}

/*********************************************************************
** Function: typeComparator
** Description: Compares the types of two Automobile objects
** Parameters: two Automobile objects
** Pre-Conditions:
** Post-Conditions: a boolean value is returned
*********************************************************************/
function typeComparator( auto1, auto2){
    var oneType = convertAutoTypeInt(auto1.type); //Get an integer to represent the type order weight
    var twoType = convertAutoTypeInt(auto2.type);
    if (oneType == twoType){                //If the types are equal check the years, the vehicle with the
      if (yearComparator(auto1, auto2))     //earlier year is greater
        return true;
      else
        return false;
    }
    if (oneType > twoType)
      return true;
    else
      return false;
}

/*********************************************************************
** Function: convertAutoTypeInt
** Description: Returns an integer that represents the weight of the vehicle type
** Parameters: an Automobile type
** Pre-Conditions:
** Post-Conditions: returns an integer representing the weight of the vehicle
** type
*********************************************************************/
function convertAutoTypeInt(autoType){
  var type = 0;
  switch (autoType.toLowerCase()){  //Assign a weight to a the vehicle type contained in autoType
    case "roadster":
      type = 5;
      break;
    case "pickup":
      type = 4;
      break;
    case "suv":
      type = 3;
      break;
    case "wagon":
      type = 2;
      break;
    default:
      type = 1;
  }
  return type;
}

/*********************************************************************
** Function: outputArr
** Description: outputs the logMe function for each element in an array of
** Automobile objects
** Parameters: the array to be logged to the console, a boolean value representing
** whether or not to display the vehicle type
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
function outputArr(array, displayWhat){
  for (var i = 0; i < array.length; i++){
    array[i].logMe(displayWhat);
  }
}

/*********************************************************************
** Function: displaySorted
** Description: Called to display an array of Automobile objects sorted several ways
** Parameters:
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
function displaySorted(){
  console.log("*****\n");
  sortArr(yearComparator, automobiles);
  console.log("The cars sorted by year are:\n");
  outputArr(automobiles, false);

  console.log("\n")
  sortArr(makeComparator, automobiles);
  console.log("The cars sorted by make are:\n");
  outputArr(automobiles, false);

  console.log("\n")
  sortArr(typeComparator, automobiles);
  console.log("The cars sorted by type are:\n");
  outputArr(automobiles, true);
  console.log("*****\n");
}

displaySorted();
