
//Week 4: Tuesday 4/25/2023
//Error Handling!

//REad is a trait that stdin implements
use std::io::Read;
use std::convert::TryFrom;
use std::error::Error;

fn getchar_warn(){
    //stdin is a function we call to handle standard input
    //parallelism would be terrible if stdinput was a global vairable
    //what we get back from stdin is a handle
    //calling .lock() locks it so we own it for the duration of our function
    //locking isn't necessary, butt doesn't hurt
    let mut stdin = std::io::stdin().lock();
    //there is no good method that reads a character from standard input
    //so lets make a buffer, a mutable slice of u8's
    let mut buf = [0u8]; //this is a mutable array that hold one u8, length of one
    //lets read into it
    //rust knows how many bytes it needs to read, with read_exact thanks to the fat pointer &
    stdin.read_exact(&mut buf).unwrap(); //unwrap the result read_exact returns
    //With this version, rusts compiler will warn us
    println!("{}", char::try_from(buf[0]).unwrap());
}

//Problem here is what if we give it something bigger than a u8, it'll read that first u8n byte
//RESULTS: we use this for error handling,we wrap the return value in a result
//Anything that returns with an error, is returning with a result
//Result carries the error!
//Generally we only use "Option" is where no returning a value isn't an error (when we actually want to return no value)
fn getchar_almost(){
    let mut stdin = std::io::stdin().lock();
    let mut buf = [0u8]; //this is a mutable array that hold one u8
    //lets read into it
    //rust knows how many bytes it needs to read, with read_exact thanks to the fat pointer &
    let result = stdin.read_exact(&mut buf); //unwrap the result read_exact returns
    //Here is the fix:
    match result {
        Ok(_) => {
            println! ("{}", char::try_from(buf[0]).unwrap());
        },
        Err(e) => {
            assert_eq!(0, buf[0]);
            println!("read exact: {}", e); //this allows custom error message
        },
    }
}

//What's the unwrap going to do if we try to type something that is outside the ASCII range
//(the high bit set)
//The unwrap will panic, and we will lose our error
//So instead of unwrap, lets match
fn getchar_better(){
    let mut stdin = std::io::stdin().lock();
    let mut buf = [0u8]; //this is a mutable array that hold one u8
    //lets read into it
    //rust knows how many bytes it needs to read, with read_exact thanks to the fat pointer &
    let result = stdin.read_exact(&mut buf); //unwrap the result read_exact returns
    //Here is the fix:
    match result {
        Ok(_) => {
            //check that what we got is a valid ascii character
            match char::try_from(buf[0]){
                Ok(ch) => println!("{}", ch),
                Err(e) => println!("read_exact: bad character"),
            }
        },
        Err(e) => {
            assert_eq!(0, buf[0]);
            println!("read exact: {}", e); //this allows custom error message
        },
    }
}
//but the code above is kind of ugly, can we make it betteR?

//Error is a trait!
//start by making a generic function out of the get_char work
//But this function
fn get_ascii_char() -> Result<char, Box<dyn Error>> {
    let mut stdin = std::io::stdin();
    let mut buf = [0u8]; //this is a mutable array that hold one u8
    //lets read into it
    //rust knows how many bytes it needs to read, with read_exact thanks to the fat pointer &
    let result = stdin.read_exact(&mut buf); //unwrap the result read_exact returns
    let byte = match result {
        Ok(()) => buf[0],
        //
        Err(e) => return Err(Box::new(e)),
    };
    match char::try_from(byte) {
        Ok(ch) => Ok(ch),
        Err(e) => Err(Box::new(e)),
    };
}

//Now just call the generic function
fn getchar_even_better(){
    match get_ascii_char() {
        Ok(ch) => println!("{}", ch),
        Err(e) => println!("get ascii char: {}", ch),
    }
}


//BUT, so many match statements! What to do?
//Use the try operator, the ? operator
//It says if the expression to my left must be type result or option, and if it is a
//result or option that is an error result, we will immediately return that error
//Otherwise proceed with the code
//We put the Ok(ch) at the end to return the ch if we didn't encounter any errors
//This allows shorthand for all those match statements
//NOTE: the ? will return on Err from the enclosing function
//TODO why static? This just ensures we can pass around the error type and be ok
fn get_ascii_char_better() -> Result<char, Box<dyn Error + 'static>> {
    let mut stdin = std::io::stdin();
    let mut buf = [0u8]; //this is a mutable array that hold one u8
    stdin.read_exact(&mut buf)?; //This retunrs a unit on Ok(), so no need to catch anything
    let byte = buf[0];
    let ch = char::try_from(byte)?; //here we want to actual value of the char, and save it to ch
    //if we donm't fail on the previous two ? marks, then you return the value
    Ok(ch);
}

//---------Lets talk about RUST MODULES for a bit!--------------------------------
//make a module in the same crate as main.rs, lets say its in a file called stuff.rs
//Notice the "pub" keyword is necessary or you can't share it
//Three visibilities: default is private, pub is pubic, third is....pub(crate) it's pubnlic to this whole crate,
//but not the outside world (protects it from the consumer of the library)

pub fn f(){
    println!("Hello");
}
//If you want to use that module: pub mod stuff; at the top of main.rs
//Then call stuff::f()
//What about a sub module?
//Imagine we have a directory in src called stuff, just make sure it has a mod.rs file in it
//And it will work the same
//Just type: stuff::morestuff::fn_in_more_stuff() to access it from main
//importing stuff to main, will get you access to stuffs sub-files here

//NOTE: in a library, we'd rather handle errors like this than simply have the program panic
fn main() {
    println!("Hello, world!");
}
