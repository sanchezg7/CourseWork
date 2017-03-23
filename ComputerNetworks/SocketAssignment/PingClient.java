import java.io.*;
import java.net.*;
import java.util.*;
import java.net.InetAddress;

public class PingClient
{
	// milliseconds
	public static void main(String[] args) throws Exception
	{
        List<Long> rtts = new ArrayList<Long>();
        // Get command line argument.
        if (args.length < 1) {
            System.out.println("Required arguments: host port");
            return;
        }
        String hostname = args[0];
        int port = Integer.parseInt(args[1]);
        
        DatagramSocket socket = new DatagramSocket(); //no bind to a port
        socket.setSoTimeout(1000); //one second block
        InetAddress host = InetAddress.getByName(hostname);
        int successfulPackets = 0;
        
        for(int i = 0; i < 10; ++i)
        {
            long start = System.currentTimeMillis();
            try{
            //byte[] payload = new byte[1024];

            byte[] payload = new String ("PING " + i + " " +(start/1000)).getBytes();
            
            DatagramPacket packet = new DatagramPacket(payload, payload.length, host, port);
			//build the packet, append PING sequenceNumber CRLF
            socket.send(packet);
            DatagramPacket response = new DatagramPacket(new byte[1024], 1024);
            socket.receive(response);
            long end = System.currentTimeMillis();
            long rtt = end - start;
            rtts.add(rtt);
            print(response);
            System.out.println("\nRound trip: " + rtt + " ms");
            ++successfulPackets;
            }catch (SocketTimeoutException e){
                System.out.println("Packet " + i + " lost.");
            }
       }
        calculations(rtts);
     }
   
    public static void print(DatagramPacket response) throws Exception{

        byte[] buf = response.getData();
        BufferedReader reader = new BufferedReader(new InputStreamReader( new ByteArrayInputStream(response.getData())));
        System.out.print(response.getAddress().getHostAddress() + " - replied " + reader.readLine());
    } 
    public static List<Long> calculations (List<Long> rtts){
        long sum = 0;
        long min = Long.MAX_VALUE;
        long max = Long.MIN_VALUE;
        long avg = 0;

        List<Long> calcs = new ArrayList<Long>();
        for(int i = 0; i < rtts.size(); ++i){
            sum += rtts.get(i);
            if(rtts.get(i) < min){
                min = rtts.get(i);
            }else if(rtts.get(i) > max){
                max = rtts.get(i);
            }
        }
        //average
        avg = sum/rtts.size();
        calcs.add(avg);
        //min
        calcs.add(min);
        //max
        calcs.add(max);


        System.out.println("Average: " + avg + 
                          " Min: " + min +
                           " Max: " + max);
        return null;
    }
} 




