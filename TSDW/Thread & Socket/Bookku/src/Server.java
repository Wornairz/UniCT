
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;


public class Server {

    public static void main(String[] args) throws IOException {

        ServerSocket server = new ServerSocket(39939);
        Socket client;
        System.out.println("Starting BOOKKU server...");
        
        Map<String, Integer> libri = new HashMap<>();
        libri.put("Metro 2033", 10);
        libri.put("Metro 2034", 1);
        libri.put("Metro 2035", 7);
        libri.put("Harry Fotters", 2000);
        libri.put("Mago Merlino", 364);
        
        while(true){
            client = server.accept();
            System.out.println("Client: " + client.getInetAddress().getHostName() + " connesso");
            BufferedReader input = new BufferedReader(new InputStreamReader(client.getInputStream()));
            PrintWriter output = new PrintWriter(client.getOutputStream(), true);
            
            output.println("Benvenuto in BOOKKU! Invia la stringa quit per terminare la connessione");
            String request;
            do{
                request = input.readLine();
                String [] s = request.split(",");
                if(s.length == 0){
                    output.println("Che cazzo sei scemo? Il formato del mex non è corretto. Manna <titolo,numero>");
                    continue;
                }
                if(libri.containsKey(s[0]) && libri.get(s[0]) >= Integer.parseInt(s[1])){
                    output.println("Buone notizie! Il libro è disponibile! Se hai altre richieste, invia un altro messaggio, altrimenti invia quit.");
                } else {
                    output.println("Cattive notizie! Il libro NON è disponibile :c ! Se hai altre richieste, invia un altro messaggio, altrimenti invia quit.");
                }
            }while(request != null && !request.equals("quit"));
            
            output.println("Piacere di essere stato utile, ciao stronzo");
            System.out.println("Client: " + client.getInetAddress().getHostName() + " disconnesso");
            client.close();
        }  
    }
}
