
// for in

var a = {
         "prop1" : 3, 
         "prop2" : undefined, 
         "prop3" : null,
         "prop4" : "This is prop 4",
         "prop5" : true
        };
console.dir(a);
console.log("typeof a is " + typeof a);
for (var propName in a)
{
    console.log(propName + " " + a[propName]);
}



var b = [ 1, 2, 3];
console.dir(b);
console.log("typeof b is " + typeof b);
console.log("b is Array ? " + Array.isArray(b));
for (var propName in b)
{
    console.log(propName + " " + b[propName]);
}

console.dir(global);
