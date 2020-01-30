import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Server {

	public static void main(String[] args) throws IOException {
		ServerSocket server = new ServerSocket(3233);
		Socket client;
		BufferedReader input;
		PrintWriter output;
		String messaggio;
		InetAddress lastIP = null;
		List<InetAddress> banned = new ArrayList<>();
		
		while(true) {
			System.out.println("In attesa di un client...");
			client = server.accept();
			System.out.println("Il client " + client.getInetAddress().getHostName() + " si è connesso!");
			input = new BufferedReader(new InputStreamReader(client.getInputStream()));
			output = new PrintWriter(client.getOutputStream(), true);
			
			if(client.getInetAddress().equals(lastIP)) {
				banned.add(client.getInetAddress());
				output.println("BANNED");
				continue;
			}
			else if(banned.contains(client.getInetAddress())) {
				output.println("BANNED");
				continue;
			}
			
			lastIP = client.getInetAddress();
			
			while(true) {
				messaggio = input.readLine();
				if(messaggio == null) {
					System.out.println("La connessione con il client è stata interrotta.");
					break;
				}
				if(messaggio.equals("TIME"))
					output.println(System.currentTimeMillis());
				else
					output.println("N/A");
			}
		}
	}

}
