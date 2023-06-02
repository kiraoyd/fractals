fn main() {
    println!("Hello, world!");
}

fn parallel(){
    let mut tids = Vec::new();  //we can make a vec of thread tids
    //threads take a closure that takes no args
    //It collects the thread results
    //If you mark this closure as a move closure, it will move memory and data into the thread
    //Arc is also a way to share data across threads
    //You use Arc for thing you want to happen atomically,like updating reference counts
    //The compiler just won't let you send plain RC's between threads
    //Send is a marker type that lets items be sent across threads

    for _ in 0..n {
        let tid = std::thread::spawn(|| {
            let rands = make_rands(); //see examples for the code for thie function
            stats(&rands)
        });
    tids.push(tid);
    }
    for tid in tids{
        println!("{:?}", tid.join().unnwrap()); //at the end, if the join is successful it unwraps the result to get Some() or None()
        //Remember, unwrap() panics when it receives a None()
    }
}
