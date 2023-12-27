use pgbar::{ProgressBar, Style};

fn main() {
    progressBar("test".to_string());
}

fn progressBar(name: String) {
    let mut pb = ProgressBar::new(100, 10, Style::default());
    println!("Progrss of {name}: ");
    pb.track();
}
