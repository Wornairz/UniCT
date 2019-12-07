/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dio.del.tuno;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

/**
 *
 * @author danilosantitto
 */
public class Hydra {

    public int getNumeroTeste() {
        return numeroTeste;
    }
    private Map<Integer, String> teste;
    private int numeroTeste;

    Hydra(int numeroTeste){
        this.numeroTeste = numeroTeste;
        teste = new HashMap<>();
        for(int i = 1; i <= numeroTeste; i++)
            teste.put(i, Elemento.getEffettoRandom());
    }

    public synchronized boolean isDead() {
        return numeroTeste == 0;
    } 
    
    public synchronized boolean attack(String spada){  
        if(!isDead() && isRightEffect(spada)){
            numeroTeste--;
            return true;
        }        
        return false;
    }
    
    public synchronized boolean isRightEffect(String spada){
        return teste.get(numeroTeste).equals(spada);
    }
}
