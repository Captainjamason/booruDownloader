use pgbar::{ProgressBar, Style};
use anyhow::{Result, Ok, Error};
use reqwest::Response;
use std::{fs::File, io::{copy, Cursor}};

#[tokio::main]
async fn main() -> Result<()> {
    match downloadImage().await {
        std::result::Result::Ok(_) => println!("image downloaded"),
        Err(e) => println!("err"),
    }
    Ok(())
}

async fn downloadImage()-> Result<()>{
    let response = reqwest::get("https://testbooru-cdn.donmai.us/original/3a/0e/3a0e769991323dcf9748adba9ab530dc.jpgjpg").await?;
    let mut file = File::create("./test.jpg")?;
    let mut content = Cursor::new(response.bytes().await?);
    copy(&mut content, &mut file)?;

    Ok(())
}

fn progressBar(name: String) {
    let mut pb = ProgressBar::new(100, 10, Style::default());
    println!("Progrss of {name}: ");
    pb.track();
}
