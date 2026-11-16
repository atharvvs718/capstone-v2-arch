package com.example;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class AppTest {

    @Test
    public void testApp() {
        assertTrue(true);
    }

    @Test
    public void testAdd() {
        assertEquals(5, App.add(2, 3));
    }
}
