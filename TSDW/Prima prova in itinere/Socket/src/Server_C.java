import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Server_C {

	public static void main(String[] args) throws IOException {
		ServerSocket server = new ServerSocket(7777);
		while(true) {
			Socket client = server.accept();
			BufferedReader input = new BufferedReader(new InputStreamReader(client.getInputStream()));
			PrintWriter output = new PrintWriter(client.getOutputStream(), true);
			
			String str = input.readLine();
			System.out.println(str);
			output.println(MUL(str));
			client.close();
		}

	}

	public static int MUL(String str) {
		return 0;
	}
}
