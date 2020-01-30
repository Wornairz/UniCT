import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class Client {

	public static void main(String[] args) throws UnknownHostException, IOException {
		Socket conn = new Socket("127.0.0.1", 3233);
		BufferedReader input = new BufferedReader(new InputStreamReader(conn.getInputStream()));
		PrintWriter output = new PrintWriter(conn.getOutputStream(), true);
		
		output.println("TIME");
		System.out.println(input.readLine());
	}

}
