import java.util.Scanner;

public class Menu {
    private Organization organization;
    private Scanner scanner;

    public Menu(Organization org) {
        this.organization = org;
        this.scanner = new Scanner(System.in);
    }

    public void start() {
        boolean running = true;

        while (running) {
            printMainMenu();
            System.out.print("➡ Επιλέξτε ενέργεια: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); 

            switch (choice) {
                case 1:
                    organization.listEntities();
                    break;
                case 2:
                    organization.listDonators();
                    break;
                case 3:
                    organization.listBeneficiaries();
                    break;
                case 0:
                    running = false;
                    System.out.println("🚪 Έξοδος από το σύστημα.");
                    break;
                default:
                    System.out.println("❌ Μη έγκυρη επιλογή.");
            }
        }
    }

    private void printMainMenu() {
        System.out.println("\n=== Κύριο Μενού ===");
        System.out.println("1. Προβολή Entity");
        System.out.println("2. Προβολή Donators");
        System.out.println("3. Προβολή Beneficiaries");
        System.out.println("0. Έξοδος");
    }
}
