
public class Client {

	public static void main(String[] args) {
		Taverna taverna = new Taverna();
		taverna.inviaSpia(new SpiaDellaGilda(TipoEroe.GUERRIERO, taverna));
		taverna.inviaSpia(new SpiaMaghi(TipoEroe.MAGO, taverna));
		taverna.inviaSpia(new SpiaDellaGilda(TipoEroe.LADRO, taverna));
		
		taverna.entra(new Eroe("Guerriero forte", TipoEroe.GUERRIERO));

		
		
	}
}
