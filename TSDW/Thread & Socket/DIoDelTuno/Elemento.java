/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dio.del.tuno;

import java.util.Random;

/**
 *
 * @author danilosantitto
 */
public class Elemento {
    private static String[] effetto = {"Fuco", "Acua", "Tuno"};

    public static String getEffettoRandom() {
        Random r = new Random();
        return effetto[r.nextInt(3)];
    }
    
}
