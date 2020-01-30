/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dio.del.tuno;

/**
 *
 * @author danilosantitto
 */
public class DioDelTuno {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws InterruptedException {
        Hydra idra = new Hydra(6);
        new Thread(new Guerriero(idra, "Saro")).start();
        new Thread(new Guerriero(idra, "Harambe")).start();
        Thread mercy = new Thread(new Guaritore(idra, "Mercy"));
        mercy.start();
        mercy.join();
        System.out.println("Hydra sconfitto, ben fatto guerrieri!");
    }
    
}
