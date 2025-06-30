public class RequestDonation{
       private Entity entity;
       private double quantity;
       
       public RequestDonation(Entity entity, double quantity)
     {
        this.entity = entity;
        this.quantity = quantity;
    }

    public Entity getEntity() { return entity; }
    public double getQuantity() { return quantity; }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        RequestDonation other = (RequestDonation) obj;
        return this.entity.getId() == other.entity.getId();
    }

    @Override
    public int hashCode() {
        return Integer.hashCode(entity.getId());
    }
}
