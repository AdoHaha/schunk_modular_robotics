#!/usr/bin/env python

import math,random,pygame

                
running = True
pygame.init()
window = pygame.display.set_mode((640, 480))

fps = pygame.time.Clock()
window.fill(pygame.Color(255,255,255))
while True:
        
        fps.tick(15)
        pygame.display.update()
        #if pygame.QUIT in [e.type for e in pygame.event.get()]:
        #        break
        for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                        key=pygame.key.get_pressed()
                        print key[pygame.K_1]
                        
