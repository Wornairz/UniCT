import java.util.List;

public class Taverna extends Edificio { // ConcreteSubject
	List<Eroe> eroi; // La lista di eroi rappresenta lo stato del (concrete)subject
	Eroe last;
	
	public void entra(Eroe eroe) { //setState()
		eroi.add(eroe);
		avvertiSpia();
		this.last = eroe;
	
	}
	
	public Eroe getEroe() { //getState1()
		return last; // si può fare anche eroi.get(ultimo)
	}
	
	public List<Eroe> getEroi() { //getState2()
		return eroi;
	}

	

}
