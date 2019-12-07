/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dio.del.tuno;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author danilosantitto
 */
public class Guaritore implements Runnable{
    Hydra idra;
    private String nome;
    Guaritore(Hydra idra, String nome){
        this.idra = idra;
        this.nome = nome;
    }
    
    @Override
    public void run() {
        while(!idra.isDead()){
            try {
            Thread.sleep(1000);
            } catch (InterruptedException ex) {
            Logger.getLogger(Guaritore.class.getName()).log(Level.SEVERE, null, ex);
            }
            System.out.println(nome + ": Heroes never die!");
            synchronized(idra){
                idra.notifyAll();
            } 
        }          
    }  
}
