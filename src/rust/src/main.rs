use std::error::Error;
use once_cell::sync::Lazy;
use tokio::runtime::{self, Runtime};

mod adapter;

static RUNTIME: Lazy<Runtime> = Lazy::new(|| {
    runtime::Builder::new_multi_thread()
      .enable_io()
      .build()
      .unwrap()
});

#[tokio::main]
async fn main() -> Result<(), Box<dyn Error>> {
    println!("Hello, world!");
    let socket = adapter::socket::Socket::new();
    socket.start(4557).await;
    Ok(())
}
