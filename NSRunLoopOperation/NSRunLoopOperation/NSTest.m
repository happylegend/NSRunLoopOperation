//
//  NSTest.m
//  NSRunLoopOperation
//
//  Created by 紫冬 on 13-7-19.
//  Copyright (c) 2013年 qsji. All rights reserved.
//

#import "NSTest.h"

@implementation NSTest

-(id)init
{
    self = [super init];
    if (self)
    {
        i = 0;
    }
    
    return self;
}

//创建一个子线程，在线程的执行方法中，再启动一个NSTimer
-(void)run
{
    NSThread *thread = [[NSThread alloc] initWithTarget:self selector:@selector(count) object:nil];
    [thread start];
}

-(void)count
{
    NSTimer *timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(beginCount) userInfo:nil repeats:YES];
    
    //启动一个NSTimer以后，因为实在子线程中启动的，所以，必须将NSTimer对象加入到当前线程的runloop中，才能正常的计时
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
    [[NSRunLoop currentRunLoop] run];
}

-(void)beginCount
{
    NSLog(@"当前计数为：%d", i++);
}

@end
