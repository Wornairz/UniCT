import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Client {
	
	public static void main(String[] args) throws IOException{
		Socket conn = new Socket("127.0.0.1", 7777);
		//System.out.println(args[0]);
		BufferedReader input = new BufferedReader(new InputStreamReader(conn.getInputStream()));
		PrintWriter output = new PrintWriter(conn.getOutputStream(), true);

		String messaggio = "";
		BufferedReader tastiera = new BufferedReader(new InputStreamReader(System.in));
		messaggio = tastiera.readLine();
		
		output.println(messaggio);
		System.out.println(input.readLine());
		
		
	}
}
