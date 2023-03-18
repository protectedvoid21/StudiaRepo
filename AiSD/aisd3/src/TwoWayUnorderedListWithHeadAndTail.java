import java.lang.annotation.ElementType;
import java.util.Iterator;
import java.util.ListIterator;


public class TwoWayUnorderedListWithHeadAndTail<E> implements IList<E>{

    private class Element{
        public Element(E e) {
            object = e;
        }
        public Element(E e, Element next, Element prev) {
            object = e;
            this.next = next;
            this.prev = prev;
        }
        E object;
        Element next=null;
        Element prev=null;
    }

    Element head;
    Element tail;
    // can be realization with the field size or without
    int size;

    private class InnerIterator implements Iterator<E>{
        Element pos;
        // TODO maybe more fields....

        public InnerIterator() {
            pos = head;
        }
        @Override
        public boolean hasNext() {
            return pos.next != null;
        }

        @Override
        public E next() {
            pos = pos.next;
            return pos.object;
        }
    }

    private class InnerListIterator implements ListIterator<E>{
        Element p;
        // TODO maybe more fields....

        @Override
        public void add(E e) {
            throw new UnsupportedOperationException();
        }

        @Override
        public boolean hasNext() {
            return p.next != null;
        }

        @Override
        public boolean hasPrevious() {
            return p.prev != null;
        }

        @Override
        public E next() {
            p = p.next;
            return p.object;
        }

        @Override
        public int nextIndex() {
            throw new UnsupportedOperationException();
        }

        @Override
        public E previous() {
            p = p.prev;
            return p.object;
        }

        @Override
        public int previousIndex() {
            throw new UnsupportedOperationException();
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();

        }

        @Override
        public void set(E e) {
            p.object = e;
        }
    }

    public TwoWayUnorderedListWithHeadAndTail() {
        // make a head and a tail	
        head=null;
        tail=null;
    }
    
    private Element getElement(int index) {
        Element current = head;
        
        while(index > 0) {
            current = current.next;
            index--;
        }
        
        return current;
    }

    @Override
    public boolean add(E e) {
        Element element = new Element(e);
        
        if(head == null) {
            head = element;
            tail = element;
            return true;
        }
        
        tail.next = element;
        element.prev = tail;
        tail = element;
        return true;
    }

    @Override
    public void add(int index, E e) {
        //TODO
    }

    @Override
    public void clear() {
        head = null;
        tail = null;
    }

    @Override
    public boolean contains(E e) {
        Element current = head;
        while(current != null) {
            if(current.object.equals(e)) {
                return true;
            }
            current = current.next;
        }
        
        return false;
    }

    @Override
    public E get(int index) {
        return getElement(index).object;
    }

    @Override
    public E set(int index, E e) {
        Element element = getElement(index);
        E previousValue = element.object;
        getElement(index).object = e;

        return previousValue;
    }

    @Override
    public int indexOf(E e) {
        int index = 0;
        Element current = head;
        
        while(current != null) {
            if(current.object.equals(e)) {
                return index;
            }
            index++;
            current = current.next;
        }
        return -1;
    }

    @Override
    public boolean isEmpty() {
        return head == null;
    }

    @Override
    public Iterator<E> iterator() {
        return new InnerIterator();
    }

    @Override
    public ListIterator<E> listIterator() {
        throw new UnsupportedOperationException();
    }

    @Override
    public E remove(int index) {
        //TODO
        return null;
    }

    @Override
    public boolean remove(E e) {
        //TODO
        return true;
    }

    @Override
    public int size() {
        int size = 0;
        Element current = head;
        
        while(current != null) {
            size++;
            current = current.next;
        }
        
        return -1;
    }
    public String toStringReverse() {
        ListIterator<E> iter=new InnerListIterator();
        while(iter.hasNext())
            iter.next();
        String retStr="";
        //TODO use reverse direction of the iterator 
        return retStr;
    }

    public void add(TwoWayUnorderedListWithHeadAndTail<E> other) {
        //TODO
    }
}
