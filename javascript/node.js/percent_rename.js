#! /usr/bin/env nodejs

var fs = require('fs');

function help()
{
    console.log('no file name specified');
}

var args = process.argv.slice(2);
if (args.length == 0)
{
    help();
    process.exit(1);
}

for (var index in args)
{
    var filename = args[index];
    var new_filename = decodeURI(filename);
    fs.rename(filename, new_filename, function(){
        console.log('rename ' + filename + ' to ' + new_filename);
    });
}
