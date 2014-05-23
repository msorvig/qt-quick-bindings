// Imported C functions from libqmlbindings
mod qmlbindings {
    use std::libc::{c_int};

    #[link(name = "qmlbindings")]
    extern {
        pub fn qtMainSimple(qmlFile: &str) -> c_int;
//        pub fn qtMain(argc: c_int, argv: **c_char, qmlFile: &str) -> c_int;
    }
}

// Rust function wrappers over qmlbindings
mod qtquick {
//    use std::libc::c_int;
//    use std::str;
//    use std::ptr;

    pub fn main(qmlFile: &str) {
        unsafe { ::qmlbindings::qtMainSimple(qmlFile); };
    }

//    pub fn mainWithArgs(args: Vec<~str>, qmlFile: &str) {
//  args.iter().map ??
//        let argv = args.map(|arg| *arg.as_c_str(|buf| buf));
//        unsafe { ::qmlbindings::qtMain(argv.len() as c_int, to_unsafe_ptr(args), qmlFile); };
//    }
}

fn main() {
    qtquick::main("hello.qml");
    //qtquick::mainWithArgs(os::args(), "hello.qml",);
}