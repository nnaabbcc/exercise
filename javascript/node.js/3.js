
// switch

var i = 30;
switch (i)
{
    case 10:
        console.log('10');
        break;
    case 15:
    case 20:
        console.log('15 or 20');
        break;
    case 30:
        console.log('30');
        break;
    default:
        console.log('unknown');
}

switch ('hello world')
{
    case 'hello' + ' world':
        console.log('Greeting was found.');
        break;
    case 'goodbye':
        console.log('Closing was found.');
        break;
    default:
        console.log('Unkown');
}

var num = 25;
switch (true)
{
    case num < 0:
        console.log('less than 0');
        break;
    case num >= 0 && num <= 10:
        console.log('between 0 and 10');
        break;
    case num > 10 && num <= 20:
        console.log('between 10 and 20');
        break;
    default:
        console.log('more than 20');
}
