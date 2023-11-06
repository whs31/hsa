use std::error::Error;
use std::net::SocketAddr;
use tokio::net::UdpSocket;

pub struct Socket
{
  pub listen_port: u16
}

impl Socket
{
  const LISTEN_IP: &'static str = "0.0.0.0";
  const MAX_DATAGRAM_SIZE: u32 = 65_507;

  pub(crate) fn new() -> Self
  {
    Socket {
      listen_port: 0
    }
  }
  pub async fn start(&self, port: u16)
  {
    let listen_addr: SocketAddr = format!("{}:{}", Socket::LISTEN_IP.parse::<String>().unwrap(),
                                          port)
      .parse()
      .unwrap();
    let socket = UdpSocket::bind(listen_addr).await.unwrap();
    loop {
      Socket::read(&socket).await;
    }
  }

  async fn read(socket: &UdpSocket)
  {
    let mut data = vec![0u8; Socket::MAX_DATAGRAM_SIZE as usize];
    let len = socket.recv(&mut data).await.unwrap();
    println!(
      "Received {} bytes: {}",
      len,
      String::from_utf8_lossy(&data[..len])
    );
  }
}