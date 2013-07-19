//
//  NSTest.h
//  NSRunLoopOperation
//
//  Created by 紫冬 on 13-7-19.
//  Copyright (c) 2013年 qsji. All rights reserved.
//

/*
 NSRunLoop的使用：
 
 使用方法，在子线程中的执行方法中，若是使用NSTimer，那么需要把NSTimer添加到runloop中
 
 在Cocoa中，每个线程(NSThread)对象中内部都有一个run loop（NSRunLoop）对象用来循环处理输入事件，
 处理的事件包括两类，一是来自Input sources的异事件，一是来自Timer sources的同步事件;
 run Loop在处理输入事件时会产生通知，可以通过Core Foundation向线程中添加run-loop observers来监听特定
 事件,以在监听的事件发生时做附加的处理工作。
 
 每个run loop可运行在不同的模式下,一个run loop mode是一个集合，其中包含其监听的若干输入事件源，定时器，以及在事件发生时需要通知的run loop observers。运行在一种mode下的run loop只会处理其run loop mode中包含的输入源事件，定时器事件，以及通知run loop mode中包含的observers。
 Cocoa中的预定义模式有:
 
 Default模式
 定义：NSDefaultRunLoopMode (Cocoa) kCFRunLoopDefaultMode (Core Foundation)
 描述：默认模式中几乎包含了所有输入源(NSConnection除外),一般情况下应使用此模式。
 Connection模式
 定义：NSConnectionReplyMode(Cocoa)
 描述：处理NSConnection对象相关事件，系统内部使用，用户基本不会使用。
 Modal模式
 定义：NSModalPanelRunLoopMode(Cocoa)
 描述：处理modal panels事件。
 Event tracking模式
 定义：UITrackingRunLoopMode(iOS) NSEventTrackingRunLoopMode(cocoa)
 描述：在拖动loop或其他user interface tracking loops时处于此种模式下，在此模式下会限制输入事件的处理。例如，当手指按住UITableView拖动时就会处于此模式。
 Common模式
 定义：NSRunLoopCommonModes (Cocoa) kCFRunLoopCommonModes (Core Foundation)
 描述：这是一个伪模式，其为一组run loop mode的集合，将输入源加入此模式意味着在Common Modes中包含的所有模式下都可以处理。在Cocoa应用程序中，默认情况下Common Modes包含default modes,modal modes,event Tracking modes.可使用CFRunLoopAddCommonMode方法想Common Modes中添加自定义modes。
 获取当前线程的run loop mode
 NSString* runLoopMode = [[NSRunLoop currentRunLoop] currentMode];
 
 二.NSTimer、NSURLConnection与UITrackingRunLoopMode
 NSTimer与NSURLConnection默认运行在default mode下，这样当用户在拖动UITableView处于UITrackingRunLoopMode模式时，NSTimer不能fire,NSURLConnection的数据也无法处理。
 NSTimer的例子:
 在一个UITableViewController中启动一个0.2s的循环定时器，在定时器到期时更新一个计数器，并显示在label上。
 
 -(void)viewDidLoad
 {
 label =[[[UILabel alloc]initWithFrame:CGRectMake(10, 100, 100, 50)]autorelease];
 [self.view addSubview:label];
 count = 0;
 NSTimer *timer = [NSTimer scheduledTimerWithTimeInterval: 1
 target: self
 selector: @selector(incrementCounter:)
 userInfo: nil
 repeats: YES];
 }
 
 - (void)incrementCounter:(NSTimer *)theTimer
 {
 count++;
 label.text = [NSString stringWithFormat:@"%d",count];
 }
 
 在正常情况下，可看到每隔0.2s，label上显示的数字+1,但当你拖动或按住tableView时，label上的数字不再更新，当你手指离开时，label上的数字继续更新。当你拖动UItableView时，当前线程run loop处于UIEventTrackingRunLoopMode模式，在这种模式下，不处理定时器事件，即定时器无法fire,label上的数字也就无法更新。
 解决方法，一种方法是在另外的线程中处理定时器事件，可把Timer加入到NSOperation中在另一个线程中调度;还有一种方法时修改Timer运行的run loop模式，将其加入到UITrackingRunLoopMode模式或NSRunLoopCommonModes模式中。
 即
 [[NSRunLoop currentRunLoop] addTimer:timer forMode:UITrackingRunLoopMode];
 或
 [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
 
 NSURLConnection也是如此，见SDWebImage中的描述,以及SDWebImageDownloader.m代码中的实现。修改NSURLConnection的运行模式可使用scheduleInRunLoop:forMode:方法。
 
 NSURLRequest *request = [[NSURLRequest alloc] initWithURL:url cachePolicy:NSURLRequestReloadIgnoringLocalCacheData timeoutInterval:15];
 NSURLConnection *connection = [[[NSURLConnection alloc] initWithRequest:request delegate:self startImmediately:NO]autorelease];
 [connection scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
 [connection start];
 
 参考:
 Threading Programming Guide – Run Loops
 NSRunLoop Class Reference
 NSURLConnection Class Reference
 NSTimer Class Reference
 CFRunLoop wiki
 SDWebImage
 TestButtonDown
 NSTimerDoesntRunWhenMenuClicked
 
 */

#import <Foundation/Foundation.h>

@interface NSTest : NSObject
{
    int i;
}

-(void)run;

@end
