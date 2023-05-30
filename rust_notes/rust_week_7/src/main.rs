
//Default example
#[Derive(debug)] //lets us print the struct easily
#[cfg(not(feature = "impldefault"), derive(Default))] //if impl feature is not on, then derive Default
//Wait what is a feature? See notes
#[Derive(default)] //you can also derive default, but you need the line above as well as the one above the impl:

struct Point {
    x: usize,
    y: usize,
}

//make a default point yourself
//#[cfg(feature = "impldefault")]
impl Default for Point {
    fn default() -> Self {
        Self::new(0,0)
    }
}

//Self is literally the type you are implementing for
impl Point {
    fn new(x: usize, y:usize) -> Self {
        Self{x, y}
    }
}

fn main() {
    println!("Hello, world!");
    //set up a point here in main
    let p = Point::new(0,0);
    println!("{:?}", p);

    //or use your default implementation
    println!("{:?}", Point::default()));
    //careful tho, this makes the code less readable

    //The real point here, is to let us make an array of things with default values:
    //let pa: [Point; 3] = [Point::new(0,0); 3]; <-- this line won't work
    //The issue being, that we only make one Point with the new call, and Point is not copy
    //so there is no way for all elements to get filledin (it does NOT get called repeatedly)
    let pa: [Point; 3] = Default::default();  //but this will let us make an array of points with the default value
    let da: [Point; 3] = std::array::from_fn(|_| Point::new(0,0));  //modern rust has this function to acheive the same things


}
