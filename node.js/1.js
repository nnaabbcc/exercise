
var json = "{\"a\": 10, \"b\": 20}";

var obj = JSON.parse(json);

console.log(json);

console.log(obj);

console.log(obj.a);

console.log(obj.b);

if (undefined === obj.c)
  console.log('c is undefined');

if (obj.hasOwnProperty('c'))
  console.log('has c');
else
  console.log('has not c');

if (obj.hasOwnProperty('b'))
  console.log('has b');
else
  console.log('has not b');

console.log(obj.c);

console.log(obj.a);

console.log('end');

