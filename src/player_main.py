import socket
import select

HOST = "127.0.0.1"
PORT = 54321


class Player:
    def __init__(self) -> None:
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((HOST, PORT))
        self.state = None
        self.all_fds = [self.sock]

    def setup(self):
        self.state = self.sock.recv(1)

    def run(self):
        self.setup()

        print("Connected. Waiting for Opponent.")
        
        working_fds = self.all_fds[:]

        select_response, _, _ = select.select(working_fds, [], [])

        if self.sock in select_response:
            self.state = self.sock.recv(1)
        
        self.close_everything()

    def close_everything(self):
        self.sock.close()


if __name__ == "__main__":
    player = Player()
    player.run()
