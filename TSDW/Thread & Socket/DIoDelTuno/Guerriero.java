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
public class Guerriero implements Runnable {

    private Hydra idra;
    private String nome;

    Guerriero(Hydra idra, String nome) {
        this.idra = idra;
        this.nome = nome;
    }

    @Override
    public void run() {
        while (!idra.isDead()) {
            String effetto = Elemento.getEffettoRandom();
            System.out.println(nome + ": sta attaccando con spada " + effetto);
            if (idra.attack(effetto)) {
                System.out.println("\t\t" + nome + ": ha attaccato con successo, numero teste: " + idra.getNumeroTeste());
                try {
                    Thread.sleep(100);
                } catch (InterruptedException ex) {
                    Logger.getLogger(Guerriero.class.getName()).log(Level.SEVERE, null, ex);
                }
            } else {
                    System.out.println("\t" + nome + ": sono stato stunnato... ahia");
                    
                    synchronized(idra){
                        try {
                            idra.wait();
                        } catch (InterruptedException ex) {
                            Logger.getLogger(Guerriero.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
            }
        }
            
    }
}
