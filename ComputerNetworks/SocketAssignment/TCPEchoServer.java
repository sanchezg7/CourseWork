import java.net.*; // for Socket, ServerSocket, and InetAddress
import java.io.*; // for IOException and Input/OutputStream

public class TCPEchoServer {
    private static final int BUFSIZE = 32; // SIZE OF RECEIVE BUFFER

    public static void main(String[] args) throws IOException {
        if(args.length != 1) {
            throw new IllegalArgumentException("Parameter(s): <Port>");
        }

        int servPort = Integer.parseInt(args[0]);

        // Create a server socket to accept client connection requests
        ServerSocket servSock = new ServerSocket(servPort);

        int recvMsgSize; // Size of received message
        byte[] receiveBuf = new byte[BUFSIZE]; // Receive buffer

        while(true) {
            Socket cIntSock = servSock.accept(); // Get client information
            SocketAddress clientAddress = cIntSock.getRemoteSocketAddress();
            System.out.println("Handling client at " + clientAddress);
            InputStream in = cIntSock.getInputStream();
            OutputStream out = cIntSock.getOutputStream();

            // Receive until client closes connection, indicated by -1
            while((recvMsgSize = in.read(receiveBuf)) != -1) {
                        out.write(receiveBuf, 0, recvMsgSize);
                    }
            // Close the socket. We are done with this client!
            cIntSock.close();

            return;
        }
    }
}
