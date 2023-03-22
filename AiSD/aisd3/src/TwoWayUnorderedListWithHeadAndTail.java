import java.lang.annotation.ElementType;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.NoSuchElementException;


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

    int size;

    private class InnerIterator implements Iterator<E>{
        Element pos;
        
        public InnerIterator() {
            pos = head;
        }
        @Override
        public boolean hasNext() {
            return pos != null;
        }

        @Override
        public E next() {
            E value = pos.object;
            pos = pos.next;
            return value;
        }
    }

    private class InnerListIterator implements ListIterator<E>{
        Element p;
        private int index = 0;

        public InnerListIterator() {
            p = head;
        }
        
        @Override
        public void add(E e) {
            throw new UnsupportedOperationException();
        }

        @Override
        public boolean hasNext() {
            return index < size;
        }

        @Override
        public boolean hasPrevious() {
            return index > 0;
        }

        @Override
        public E next() {
            E value = p.object;
            p = p.next;
            index++;
            return value;
        }

        @Override
        public int nextIndex() {
            throw new UnsupportedOperationException();
        }

        @Override
        public E previous() {
            if(!hasNext()) {
                p = tail;
            }
            index--;
            E value = p.object;
            p = p.prev;
            return value;
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
        head=null;
        tail=null;
    }
    
    private Element getElement(int index) throws NoSuchElementException {
        if(index < 0 || index > size - 1) {
            throw new NoSuchElementException();
        }
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
        
        if(size == 0) {
            head = element;
            tail = element;
            size++;
            return true;
        }
        
        tail.next = element;
        element.prev = tail;
        tail = element;
        size++;
        return true;
    }

    @Override
    public void add(int index, E e) throws NoSuchElementException {
        if(index < 0 || index > size - 1) {
            throw new NoSuchElementException();
        }
        
        Element created = new Element(e);
        size++;
        
        if(index == 0) {
            created.next = head;
            head.prev = created;
            head = created;
        }
        else if(index == size - 1) {
            created.next = tail;
            created.prev = tail.prev;
        }
        else {
            Element found = getElement(index);
            created.next = found;
            created.prev = found.prev;
            found.prev.next = created;
            found.prev = created;
        }
    }

    @Override
    public void clear() {
        head = null;
        tail = null;
        size = 0;
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
    public E get(int index) throws NoSuchElementException {
        return getElement(index).object;
    }

    @Override
    public E set(int index, E e) throws NoSuchElementException {
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
        return size == 0;
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
    public E remove(int index) throws NoSuchElementException {
        Element element = getElement(index);
        
        if(index == 0) {
            if(size == 1) {
                clear();
            }
            else {
                head = head.next;
                head.prev = null;
                size--;
            }
            return element.object;
        }
    
        element.prev.next = element.next;
        
        
        if(index == size - 1) {
            tail = element.prev;
        }
        else {
            element.next.prev = element.prev;
        }
        size--;
        return element.object;
    }

    @Override
    public boolean remove(E e) {
        if(isEmpty()) {
            return false;
        }
        Element current = head;
        
        if(current.object.equals(e)) {
            if(size == 1) {
                clear();
            }
            else {
                head = head.next;
                head.prev = null;
                size--;
            }
            return true;
        }
        
        int index = 1;
        
        while(index < size) {
            if(current.object.equals(e)) {
                current.prev.next = current.next;
                current.next.prev = current.prev;
                size--;
                return true;
            }
            current = current.next;
            index++;
        }
        
        if(current.object.equals(e)) {
            current.prev.next = null;
            tail = current.prev;
            size--;
            return true;
        }
        return false;
    }

    @Override
    public int size() {
        return size;
    }
    
    public String toStringReverse() {
        ListIterator<E> iter=new InnerListIterator();
        StringBuilder retStr= new StringBuilder();
        
        while(iter.hasNext()) {
            iter.next();
        }
        
        while(iter.hasPrevious()) {
            retStr.append("\n" + iter.previous().toString());
        }
        
        return retStr.toString();
    }

    public void add(TwoWayUnorderedListWithHeadAndTail<E> other) {
        if(other.isEmpty() || other == this) {
            return;
        }

        if (head == null) {
            head = other.head;
            tail = other.tail;
        } else {
            tail.next = other.head;
            other.head.prev = tail;
            tail = other.tail;
        }

        size += other.size;
        other.clear();
    }
}
