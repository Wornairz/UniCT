/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientPac;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

/**
 *
 * @author Alessandro
 */
public class client {
    public static void main(String[] args) throws IOException {
        Socket client = new Socket("localhost", 39939);
        
        BufferedReader input = new BufferedReader(new InputStreamReader(client.getInputStream()));
        PrintWriter output = new PrintWriter(client.getOutputStream(), true);
        
        BufferedReader tastiera = new BufferedReader(new InputStreamReader(System.in));
        
        String request;
        do{
            System.out.println(input.readLine());
            request = tastiera.readLine();  
            output.println(request);     
        } while(!request.equals("quit"));
            
        client.close();
    }
}
