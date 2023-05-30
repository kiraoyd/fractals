

//Week 6: Tuesday 5/9/2023
//What makes rust extra special?
//Static - compiel time, dynamic - runtime
//Rust's module system is a REAL one, worth saying

//Let's talk about 'unsafe' code. You can force Rust to let you
//share global static variables, but is it a good idea?
//So it's time to talk about Rusts REFCELL, the static cell
//look up std::cell to read about sharable mutable containers
//the set() function actually checks at runtime if that thing is safe to mutate at runtime
//If it isn't, we panic. We just traded compile time errors for runtime panics.
//Not the best trade here

//IF we wanted to make A GLOBAL AccessCounter, Rust will yell that we can't do this unless we make the code unsafe
//static mut ACCESSES: AccessCounter = AccessCounter(0);
//^^^instead of this, lets use a refcell instead
//You use these when you really need something that EVERYone can share and mutate
//Best not to use unless you have to

//A refmut guard (what the borrow_mut() returns) is what tells the refcell when a
//reference is in use. When the guard is dropped, the reference is now free
//drop the guard with drop(nameof_borrow)
//BUT rust can also be told to drop something WHEN it can be proved no one is using it anymore
//When the Rc<> wraps a Refcell, Rc keeps track of how many times its been borrowed
//When that number goes to 0, Rc triggers a drop(), it also manages lifetimes
use std::rc::RC;


use std::cell::RefCell;
struct AccessCounter(usize);

impl AccessCounter{
    fn inc(&mut self){
        self.0 += 1;
    }
    fn get(&self) -> usize {
        self.0
    }
}
//if you have a reference in a thing, you need a lifetime
struct Reader<'a>{
    counter: usize,
    accesses: &'a Rc<RefCell<AccessCounter>>,
}

impl <'a>Reader<'a>{
    fn read(&mut self) -> String {
        self.accesses.borrow_mut().inc();
        self.counter += 1;
        self.counter.to_string()
    }
}



struct Writer;

impl Writer {
    fn write(&mut self, s: & str){
    ACCESSES.inc();
    self.0 = s.to_owned();
    }
}

fn main() {
    //when you want to get to any of the access stuff, you better borrow since the accesses is wrapped in a refcell

    let accesses = RC::new(RefCell:: new(AccessCounter::default()));
    let axp = accesses.borrow_mut();
    let mut counter = AccessCounter::default():
    let mut writer = Writer{
        written: "", to_string(),
        //when we pass a clone of Rc, everyone behaves as if they have a copy of Rc
        accesses: Rc::clone(&accesses);
    };
    let mut reader = Reader{
        counter: 0,
        accesses: Rc::clone(&accesses);
    };
    //so now reader and writer have clone copies of Rc
    writer.write(&reader.read());
    //drop example
    //drop(axp);
    //println!("{:?} {:?} {:?}", writer, reader, unsafe{ &ACCESSES});
    writer.write(&reader.read());
    println!("{:?} {:?} {:?}", writer.get(), reader.get(), accesses.borrow().get());
    accesses.borrow_mut().reset();
    drop(accesses);
}
