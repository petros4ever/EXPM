import java.util.*;

public class Main {
    public static void main(String[] args) {
        try {
            Admin admin = new Admin("Maria", "6980000001");
            Organization org = new Organization("SolidarityHub", admin);

            
            Material milk = new Material("Milk", "1L carton", 1, 2.0, 4.0, 6.0);
            Material sugar = new Material("Sugar", "White, 1kg", 2, 1.0, 2.0, 3.5);
            Material rice = new Material("Rice", "Long grain", 3, 1.5, 3.0, 5.0);
            Service medical = new Service("MedicalSupport", "Basic medical care", 4);
            Service nursery = new Service("NurserySupport", "Child care assistance", 5);
            Service babysitting = new Service("BabySitting", "Home babysitting", 6);

            org.addEntity(milk);
            org.addEntity(sugar);
            org.addEntity(rice);
            org.addEntity(medical);
            org.addEntity(nursery);
            org.addEntity(babysitting);

            
            Donator donator = new Donator("Giorgos", "6991000001");
            Beneficiary anna = new Beneficiary("Anna", "6944000002", 1,org);
            Beneficiary nikos = new Beneficiary("Nikos", "6945000003", 5,org); 

            org.insertDonator(donator);
            org.insertBeneficiary(anna);
            org.insertBeneficiary(nikos);

            
            RequestDonation r1 = new RequestDonation(rice, 4.5);           
            RequestDonation r2 = new RequestDonation(medical, 1.0);        
            RequestDonation r3 = new RequestDonation(sugar, 2.5);          

            nikos.addRequest(r1,org.getEntityList());
            nikos.addRequest(r2,org.getEntityList());
            nikos.addRequest(r3,org.getEntityList());

            
            RequestDonation d1 = new RequestDonation(rice, 10.0);
            RequestDonation d2 = new RequestDonation(sugar, 5.0);
            RequestDonation d3 = new RequestDonation(milk, 6.0);
            RequestDonation d4 = new RequestDonation(medical, 2.0);

            donator.addOffer(d1, org.getEntityList());
            donator.addOffer(d2, org.getEntityList());
            donator.addOffer(d3, org.getEntityList());
            donator.addOffer(d4, org.getEntityList());

            
            donator.commitOffers(org.getCurrentDonations(), org.getEntityList());

            
            System.out.println("\n📦 Διαθέσιμες δωρεές στον οργανισμό:");
            org.getCurrentDonations().monitor();

            
            System.out.println("\n🧾 Ο Nikos κάνει commit τα αιτήματά του:");
            nikos.commitRequests(org.getEntityList(), org.getCurrentDonations());

            
            System.out.println("\n📥 Ιστορικό παραλαβών του Nikos:");
            nikos.getReceivedList().monitor();

            
            System.out.println("\n📌 Προσθήκη και διαγραφή αιτήματος από την Anna:");
            RequestDonation r4 = new RequestDonation(milk, 3.0);
            anna.addRequest(r4,org.getEntityList());
            anna.getRequestsList().monitor();
            anna.removeRequest(r4.getEntity());
            anna.getRequestsList().monitor();

            
            System.out.println("\n🔧 Ο Giorgos τροποποιεί προσφορά σε milk:");
            donator.addOffer(new RequestDonation(milk, 2.0), org.getEntityList());
            donator.getOffersList().monitor();

        } catch (Exception e) {
            System.out.println("❗ Σφάλμα: " + e.getMessage());
        }
    }
}
