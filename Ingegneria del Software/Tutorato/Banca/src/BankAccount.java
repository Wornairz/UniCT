/** Requisiti:
 * - l'account deve essere inizializzato con un credito nullo o positivo
 * - fornire un'operazione di versamento e una di prelievo
 * - un'operazione di prelievo restituisce il credito ritirato
 * - con un versamento di almeno 1000€ l'account diventa premium
 * - con un account premium, ogni versamento viene maggiorato del 5%
 * - un credito negativo è possibile solo con un account premium
 * - con un account normale, un prelievo oltre la disponibilità causa il prelievo di tutto il credito disponibile
 * - deve essere possibile ottenere informazioni sullo stato del conto
 */


public class BankAccount {
	private boolean premium = false;
	private double credit = 0.0;
	
	public BankAccount(double init) {
		deposit(init);
	}
	
	public void deposit(double amount) {
		if (amount >= 1000) premium = true;
		
		if (premium) amount *= 1.05;
		credit += amount;
	}
	
	public double withdraw(double amount) {
		double cash = 0.0;
		
		if (premium || credit-amount>=0) {
			credit -= amount;
			cash = amount;
		}
		else {
			cash = credit;
			credit = 0;
		}
		
		return cash;
	}
	
	public boolean isPremium() {
		return premium;
	}
	
	public double getCredit() {
		return credit;
	}
	

}